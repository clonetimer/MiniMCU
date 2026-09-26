#include "platform.h"

void uart_putc(char character) {
    while ((REG32(UART_BASE + 8) & 1u) == 0) {
    }
    REG32(UART_BASE) = (unsigned char)character;
}

void uart_puts(const char *text) {
    while (*text != '\0') {
        uart_putc(*text++);
    }
}

void uart_flush(void) {
    while ((REG32(UART_BASE + 8) & 4u) == 0) {
    }
}

void sim_exit(unsigned exit_code) {
    uart_flush();
    REG32(0x4000f000u) = (exit_code << 1) | 1u;
    for (;;) {
        __asm__ volatile("nop");
    }
}

uint64_t timer_now(void) {
    uint32_t high_word_before;
    uint32_t low_word;
    uint32_t high_word_after;

    // RV32 读取 64-bit MTIME 时，用 high/low/high 避免低 32 位翻转造成撕裂。
    do {
        high_word_before = REG32(MTIME_BASE + 4);
        low_word = REG32(MTIME_BASE);
        high_word_after = REG32(MTIME_BASE + 4);
    } while (high_word_before != high_word_after);

    return ((uint64_t)high_word_before << 32) | low_word;
}

void timer_compare(uint64_t compare_value) {
    // 先把低 32 位写成最大值，避免更新高半字期间产生瞬时误触发。
    REG32(MTIMECMP_BASE) = 0xffffffffu;
    REG32(MTIMECMP_BASE + 4) = (uint32_t)(compare_value >> 32);
    REG32(MTIMECMP_BASE) = (uint32_t)compare_value;
}

__attribute__((weak))
void trap_handler_c(uint32_t cause,
                    uint32_t exception_pc,
                    uint32_t trap_value) {
    (void)cause;
    (void)exception_pc;
    (void)trap_value;
    uart_puts("unexpected trap\n");
    sim_exit(2);
}
