#include "platform.h"

static volatile unsigned timer_interrupt_count;

/*
 * trap.S 按 a0/a1/a2 传入 mcause、mepc、mtval。
 * 这里明确写出每个参数对应的 CSR，避免只看 cause/epc/value 猜语义。
 */
void trap_handler_c(uint32_t mcause_value,
                    uint32_t exception_program_counter,
                    uint32_t trap_value) {
    (void)exception_program_counter;
    (void)trap_value;

    if (mcause_value != 0x80000007u) {
        sim_exit(20);
    }

    ++timer_interrupt_count;

    /* MTIME 时基为 1 MHz，因此 +1000 tick 对应下一次约 1 ms 后触发。 */
    timer_compare(timer_now() + 1000U);
}

int main(void) {
    timer_compare(timer_now() + 1000U);

    /* mie.MTIE=1，同时打开 mstatus.MIE。 */
    __asm__ volatile(
        "li t0, 128; csrs mie, t0; csrsi mstatus, 8"
        ::: "t0", "memory");

    while (timer_interrupt_count < 5U) {
        /* 等待五次 Machine Timer interrupt。 */
    }

    __asm__ volatile("csrci mstatus, 8" ::: "memory");
    uart_puts("bare-metal timer interrupt: 5 ticks OK\n");
    return 0;
}
