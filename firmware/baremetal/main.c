#include "platform.h"

/*
 * 这两个对象分别验证启动代码是否正确初始化 .data 和清零 .bss。
 */
static volatile uint32_t initialized_data = 0x11223344u;
static volatile uint32_t zero_initialized_data[16];

__attribute__((noinline)) static uint32_t fibonacci(unsigned sequence_index) {
    uint32_t previous_value = 0;
    uint32_t current_value = 1;

    while (sequence_index-- != 0U) {
        const uint32_t next_value = previous_value + current_value;
        previous_value = current_value;
        current_value = next_value;
    }
    return previous_value;
}

int main(void) {
    if (initialized_data != 0x11223344u) {
        return 10;
    }

    for (unsigned element_index = 0; element_index < 16U; ++element_index) {
        if (zero_initialized_data[element_index] != 0U) {
            return 11;
        }
    }

    /* 函数调用和局部变量同时验证栈、调用约定与 RV32I 算术路径。 */
    if (fibonacci(12U) != 144U) {
        return 12;
    }

    /* GPIO +8 是方向寄存器，+4 是输出寄存器；这里让 pin0 输出高电平。 */
    REG32(GPIO_BASE + 8U) = 1U;
    REG32(GPIO_BASE + 4U) = 1U;

    uart_puts("bare-metal C: PASS (data/bss/stack/calls/GPIO/UART)\n");
    return 0;
}
