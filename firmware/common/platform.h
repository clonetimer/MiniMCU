#ifndef MINICPU_PLATFORM_H
#define MINICPU_PLATFORM_H

#include <stdint.h>

// 32-bit MMIO 访问宏。参数明确表示系统物理地址。
#define REG32(address) (*(volatile uint32_t *)(uintptr_t)(address))

#define GPIO_BASE     0x40000000u
#define UART_BASE     0x40002000u
#define MTIME_BASE    0x0200bff8u
#define MTIMECMP_BASE 0x02004000u

void uart_putc(char character);
void uart_puts(const char *text);
void uart_flush(void);
void sim_exit(unsigned exit_code) __attribute__((noreturn));
uint64_t timer_now(void);
void timer_compare(uint64_t compare_value);

// cause / exception_pc / trap_value 分别对应 mcause / mepc / mtval。
void trap_handler_c(uint32_t cause,
                    uint32_t exception_pc,
                    uint32_t trap_value);

#endif
