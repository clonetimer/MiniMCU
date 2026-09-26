#include "FreeRTOS.h"
#include "task.h"
#include "platform.h"

// 两个 worker 的递增计数器。若抢占式调度正常，两者都应持续前进。
static volatile uint32_t worker_run_counts[2];
static volatile uint32_t tick_hook_count;

static void worker_task(void* task_argument) {
    const unsigned worker_id = (unsigned)(uintptr_t)task_argument;
    volatile uint32_t stack_guard_words[8];

    // 在任务栈上放置一组可预测的保护值，用来检测上下文切换期间的栈破坏。
    for (unsigned guard_index = 0; guard_index < 8; ++guard_index) {
        stack_guard_words[guard_index] =
            0x12345670u + guard_index + worker_id;
    }

    uart_putc(worker_id != 0 ? 'B' : 'A');

    // 两个 worker 都不主动阻塞或 yield：只有时钟 tick 触发的抢占正常，
    // 两个计数器才会同时增长。
    for (;;) {
        for (unsigned guard_index = 0; guard_index < 8; ++guard_index) {
            const uint32_t expected_guard_value =
                0x12345670u + guard_index + worker_id;
            if (stack_guard_words[guard_index] != expected_guard_value) {
                sim_exit(21);
            }
        }
        ++worker_run_counts[worker_id];
    }
}

static void monitor_task(void* unused_task_argument) {
    (void)unused_task_argument;

    // 等待至少 30 个系统 tick，让两个 worker 有足够时间被轮流抢占运行。
    vTaskDelay(30);

    const BaseType_t both_workers_ran =
        worker_run_counts[0] != 0 && worker_run_counts[1] != 0;
    const BaseType_t tick_interrupts_arrived = tick_hook_count >= 30;
    const BaseType_t scheduler_time_advanced = xTaskGetTickCount() >= 30;

    if (!both_workers_ran || !tick_interrupts_arrived ||
        !scheduler_time_advanced) {
        sim_exit(22);
    }

    taskENTER_CRITICAL();
    uart_puts("\nFreeRTOS: preemption/tick/context/stack PASS\n");
    sim_exit(0);
}

void vApplicationTickHook(void) {
    ++tick_hook_count;
}

void vApplicationMallocFailedHook(void) {
    sim_exit(23);
}

void vApplicationStackOverflowHook(TaskHandle_t task_handle,
                                   char* task_name) {
    (void)task_handle;
    (void)task_name;
    sim_exit(24);
}

void minicpu_assert_failed(const char* source_file_name,
                           unsigned source_line_number) {
    (void)source_file_name;
    (void)source_line_number;
    sim_exit(25);
}

void freertos_risc_v_application_interrupt_handler(void) {
    sim_exit(26);
}

void freertos_risc_v_application_exception_handler(void) {
    sim_exit(27);
}

int main(void) {
    if (xTaskCreate(worker_task, "workerA", 256,
                    (void*)(uintptr_t)0, 2, NULL) != pdPASS) {
        sim_exit(28);
    }

    if (xTaskCreate(worker_task, "workerB", 256,
                    (void*)(uintptr_t)1, 2, NULL) != pdPASS) {
        sim_exit(29);
    }

    if (xTaskCreate(monitor_task, "monitor", 384,
                    NULL, 3, NULL) != pdPASS) {
        sim_exit(30);
    }

    vTaskStartScheduler();

    // 正常情况下调度器不会返回；返回说明启动过程异常。
    sim_exit(31);
}
