#include <stddef.h>
#include <stdint.h>

#include "platform.h"

/*
 * 裸机固件没有宿主操作系统提供的 libc / compiler-rt。
 * 这里提供编译器和普通 C 代码会隐式依赖的最小运行时函数。
 *
 * 这些函数刻意使用完整的参数名，便于学习时直接看出：
 * - destination/source：源、目的缓冲区；
 * - byte_count：长度单位始终是“字节”；
 * - dividend/divisor：被除数与除数。
 */
void *memcpy(void *destination, const void *source, size_t byte_count) {
    unsigned char *destination_bytes = (unsigned char *)destination;
    const unsigned char *source_bytes = (const unsigned char *)source;

    for (size_t byte_index = 0; byte_index < byte_count; ++byte_index) {
        destination_bytes[byte_index] = source_bytes[byte_index];
    }
    return destination;
}

void *memmove(void *destination, const void *source, size_t byte_count) {
    unsigned char *destination_bytes = (unsigned char *)destination;
    const unsigned char *source_bytes = (const unsigned char *)source;

    if ((uintptr_t)destination_bytes < (uintptr_t)source_bytes) {
        for (size_t byte_index = 0; byte_index < byte_count; ++byte_index) {
            destination_bytes[byte_index] = source_bytes[byte_index];
        }
    } else {
        /* 从尾部复制，避免源区和目的区重叠时覆盖尚未读取的数据。 */
        while (byte_count != 0U) {
            --byte_count;
            destination_bytes[byte_count] = source_bytes[byte_count];
        }
    }
    return destination;
}

void *memset(void *destination, int fill_value, size_t byte_count) {
    unsigned char *destination_bytes = (unsigned char *)destination;
    const unsigned char fill_byte = (unsigned char)fill_value;

    for (size_t byte_index = 0; byte_index < byte_count; ++byte_index) {
        destination_bytes[byte_index] = fill_byte;
    }
    return destination;
}

int memcmp(const void *left_buffer, const void *right_buffer, size_t byte_count) {
    const unsigned char *left_bytes = (const unsigned char *)left_buffer;
    const unsigned char *right_bytes = (const unsigned char *)right_buffer;

    for (size_t byte_index = 0; byte_index < byte_count; ++byte_index) {
        if (left_bytes[byte_index] != right_bytes[byte_index]) {
            return left_bytes[byte_index] < right_bytes[byte_index] ? -1 : 1;
        }
    }
    return 0;
}

size_t strlen(const char *text) {
    size_t character_count = 0;
    while (text[character_count] != '\0') {
        ++character_count;
    }
    return character_count;
}

int strcmp(const char *left_text, const char *right_text) {
    while (*left_text != '\0' && *left_text == *right_text) {
        ++left_text;
        ++right_text;
    }
    return (unsigned char)*left_text - (unsigned char)*right_text;
}

char *strncpy(char *destination, const char *source, size_t destination_size) {
    size_t character_index = 0;
    for (; character_index < destination_size && source[character_index] != '\0'; ++character_index) {
        destination[character_index] = source[character_index];
    }
    for (; character_index < destination_size; ++character_index) {
        destination[character_index] = '\0';
    }
    return destination;
}

/*
 * RV32I 没有 M 扩展，因此乘除法由编译器调用这些软件辅助函数完成。
 * 算法并非为了性能，而是为了让纯 RV32I 固件不依赖外部运行库。
 */
uint32_t __mulsi3(uint32_t multiplicand, uint32_t multiplier) {
    uint32_t product = 0;
    while (multiplier != 0U) {
        if ((multiplier & 1U) != 0U) {
            product += multiplicand;
        }
        multiplicand <<= 1U;
        multiplier >>= 1U;
    }
    return product;
}

uint32_t __udivsi3(uint32_t dividend, uint32_t divisor) {
    if (divisor == 0U) {
        return UINT32_MAX;
    }

    uint32_t quotient = 0;
    uint32_t remainder = 0;
    for (unsigned bit_index = 32U; bit_index-- != 0U;) {
        const uint32_t carry_out = remainder >> 31U;
        remainder = (remainder << 1U) | ((dividend >> bit_index) & 1U);
        if (carry_out != 0U || remainder >= divisor) {
            remainder -= divisor;
            quotient |= 1U << bit_index;
        }
    }
    return quotient;
}

uint32_t __umodsi3(uint32_t dividend, uint32_t divisor) {
    const uint32_t quotient = __udivsi3(dividend, divisor);
    return dividend - __mulsi3(quotient, divisor);
}

int32_t __divsi3(int32_t dividend, int32_t divisor) {
    uint32_t unsigned_dividend = (uint32_t)dividend;
    uint32_t unsigned_divisor = (uint32_t)divisor;
    const int result_is_negative = (dividend < 0) ^ (divisor < 0);

    if (dividend < 0) {
        unsigned_dividend = 0U - unsigned_dividend;
    }
    if (divisor < 0) {
        unsigned_divisor = 0U - unsigned_divisor;
    }

    const uint32_t quotient = __udivsi3(unsigned_dividend, unsigned_divisor);
    return (int32_t)(result_is_negative ? 0U - quotient : quotient);
}

int32_t __modsi3(int32_t dividend, int32_t divisor) {
    const int32_t quotient = __divsi3(dividend, divisor);
    return (int32_t)((uint32_t)dividend -
                     __mulsi3((uint32_t)quotient, (uint32_t)divisor));
}

void abort(void) {
    /* 99 仅是本项目约定的“运行时异常退出码”。 */
    sim_exit(99);
}
