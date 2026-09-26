#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TICKLESS_IDLE 0
/* The upstream MTIME port divides this value for timer increments. In this
   platform it is MTIME's 1 MHz timebase, NOT the model CPU's 50 MHz clock. */
#define configCPU_CLOCK_HZ 1000000UL
#define configTICK_RATE_HZ 1000UL
#define configMTIME_BASE_ADDRESS 0x0200bff8UL
#define configMTIMECMP_BASE_ADDRESS 0x02004000UL
#define configTICK_TYPE_WIDTH_IN_BITS TICK_TYPE_WIDTH_32_BITS
#define configMAX_PRIORITIES 5
#define configMINIMAL_STACK_SIZE 256
#define configMAX_TASK_NAME_LEN 12
#define configTOTAL_HEAP_SIZE (32 * 1024)
#define configISR_STACK_SIZE_WORDS 512
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION 0
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 1
#define configCHECK_FOR_STACK_OVERFLOW 2
#define configUSE_MALLOC_FAILED_HOOK 1
#define configUSE_MUTEXES 1
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_COUNTING_SEMAPHORES 1
#define configUSE_TIMERS 0
#define configUSE_CO_ROUTINES 0
#define configUSE_TRACE_FACILITY 0
#define configGENERATE_RUN_TIME_STATS 0
#define configUSE_STATS_FORMATTING_FUNCTIONS 0
#define configQUEUE_REGISTRY_SIZE 0
#define configUSE_NEWLIB_REENTRANT 0
#define configENABLE_FPU 0
#define configENABLE_VPU 0
#define INCLUDE_vTaskDelay 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_xTaskGetSchedulerState 1
#ifndef __ASSEMBLER__
void minicpu_assert_failed(const char *file, unsigned line);
#define configASSERT(x) do { if(!(x)) minicpu_assert_failed(__FILE__, __LINE__); } while(0)
#endif
#endif
