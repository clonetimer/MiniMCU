#include "drivers.h"

static int wait_mask(uint32_t register_address,
                     uint32_t bit_mask,
                     uint32_t expected_value,
                     uint32_t timeout_ticks) {
    const uint64_t start_time = timer_now();
    while ((REG32(register_address) & bit_mask) != expected_value) {
        if (timer_now() - start_time >= timeout_ticks) {
            return -1;
        }
    }
    return 0;
}

void gpio_configure(uint32_t output_mask) {
    REG32(GPIO_BASE + 8) = output_mask;
}

void gpio_set(uint32_t pin_mask) {
    REG32(GPIO_BASE + 12) = pin_mask;
}

void gpio_clear(uint32_t pin_mask) {
    REG32(GPIO_BASE + 16) = pin_mask;
}

void gpio_irq_configure(uint32_t rising_edge_mask,
                        uint32_t falling_edge_mask,
                        uint32_t interrupt_enable_mask) {
    REG32(GPIO_BASE + 20) = rising_edge_mask;
    REG32(GPIO_BASE + 24) = falling_edge_mask;
    REG32(GPIO_BASE + 28) = interrupt_enable_mask;
}

void gpio_irq_clear(uint32_t pending_mask) {
    REG32(GPIO_BASE + 32) = pending_mask;
}

void irq_configure(unsigned source_id,
                   unsigned priority,
                   int enable_source) {
    if (source_id == 0 || source_id > 31) {
        return;
    }

    REG32(IRQ_BASE + 4 * source_id) = priority & 7u;
    const uint32_t old_enable_mask = REG32(IRQ_BASE + 0x104);
    REG32(IRQ_BASE + 0x104) = enable_source
        ? old_enable_mask | (1u << source_id)
        : old_enable_mask & ~(1u << source_id);
}

unsigned irq_claim(void) {
    return REG32(IRQ_BASE + 0x10c);
}

void irq_complete(unsigned source_id) {
    REG32(IRQ_BASE + 0x10c) = source_id;
}

int spi_select(int chip_select_id) {
    if (chip_select_id < -1 || chip_select_id > 3) {
        return -1;
    }
    if (wait_mask(SPI_BASE + 4, 1, 1, 10000)) {
        return -1;
    }
    REG32(SPI_BASE + 12) = (uint32_t)chip_select_id;
    return 0;
}

int spi_transfer(uint8_t transmitted_byte,
                 uint8_t *received_byte,
                 uint32_t timeout_ticks) {
    if (received_byte == 0 ||
        wait_mask(SPI_BASE + 4, 1, 1, timeout_ticks)) {
        return -1;
    }

    REG32(SPI_BASE) = transmitted_byte;
    if (wait_mask(SPI_BASE + 4, 1, 1, timeout_ticks)) {
        return -1;
    }

    *received_byte = (uint8_t)REG32(SPI_BASE);
    return 0;
}

int spi_read_register(unsigned chip_select_id,
                      uint8_t register_address,
                      uint8_t *register_value) {
    uint8_t ignored_byte;
    if (chip_select_id > 3 || register_value == 0 ||
        spi_select((int)chip_select_id)) {
        return -1;
    }

    const int transfer_failed =
        spi_transfer((uint8_t)(register_address | 0x80u),
                     &ignored_byte,
                     10000) ||
        spi_transfer(0xff, register_value, 10000);
    const int deselect_failed = spi_select(-1);
    return transfer_failed || deselect_failed ? -1 : 0;
}

int spi_write_register(unsigned chip_select_id,
                       uint8_t register_address,
                       uint8_t register_value) {
    uint8_t ignored_byte;
    if (chip_select_id > 3 || spi_select((int)chip_select_id)) {
        return -1;
    }

    const int transfer_failed =
        spi_transfer((uint8_t)(register_address & 0x7fu),
                     &ignored_byte,
                     10000) ||
        spi_transfer(register_value, &ignored_byte, 10000);
    const int deselect_failed = spi_select(-1);
    return transfer_failed || deselect_failed ? -1 : 0;
}

int flash_id(uint8_t jedec_id[3]) {
    uint8_t ignored_byte;
    if (jedec_id == 0 || spi_select(0)) {
        return -1;
    }

    int transfer_failed = spi_transfer(0x9f, &ignored_byte, 10000);
    for (unsigned byte_index = 0;
         byte_index < 3 && !transfer_failed;
         ++byte_index) {
        transfer_failed = spi_transfer(0xff, &jedec_id[byte_index], 10000);
    }
    const int deselect_failed = spi_select(-1);
    return transfer_failed || deselect_failed ? -1 : 0;
}

static int flash_send_header(uint8_t command_byte,
                             uint32_t flash_address) {
    uint8_t ignored_byte;
    return spi_transfer(command_byte, &ignored_byte, 10000) ||
           spi_transfer((uint8_t)(flash_address >> 16), &ignored_byte, 10000) ||
           spi_transfer((uint8_t)(flash_address >> 8), &ignored_byte, 10000) ||
           spi_transfer((uint8_t)flash_address, &ignored_byte, 10000);
}

static int flash_wait_ready(uint32_t timeout_ticks) {
    const uint64_t start_time = timer_now();
    for (;;) {
        uint8_t ignored_byte;
        uint8_t status_register;
        if (spi_select(0)) {
            return -1;
        }

        const int transfer_failed =
            spi_transfer(0x05, &ignored_byte, 10000) ||
            spi_transfer(0xff, &status_register, 10000);
        const int deselect_failed = spi_select(-1);
        if (transfer_failed || deselect_failed) {
            return -1;
        }
        if ((status_register & 1u) == 0) {
            return 0;
        }
        if (timer_now() - start_time >= timeout_ticks) {
            return -1;
        }
    }
}

int flash_program_byte(uint32_t flash_address, uint8_t byte_value) {
    uint8_t ignored_byte;
    if (flash_address >= 1024u * 1024u || spi_select(0)) {
        return -1;
    }

    int operation_failed = spi_transfer(0x06, &ignored_byte, 10000); // WREN
    int deselect_failed = spi_select(-1);
    if (operation_failed || deselect_failed || spi_select(0)) {
        return -1;
    }

    operation_failed =
        flash_send_header(0x02, flash_address) ||
        spi_transfer(byte_value, &ignored_byte, 10000);
    deselect_failed = spi_select(-1);
    if (operation_failed || deselect_failed) {
        return -1;
    }
    return flash_wait_ready(10000);
}

int flash_read_byte(uint32_t flash_address, uint8_t *byte_value) {
    if (byte_value == 0 ||
        flash_address >= 1024u * 1024u ||
        spi_select(0)) {
        return -1;
    }

    const int operation_failed =
        flash_send_header(0x03, flash_address) ||
        spi_transfer(0xff, byte_value, 10000);
    const int deselect_failed = spi_select(-1);
    return operation_failed || deselect_failed ? -1 : 0;
}

static int i2c_execute_command(uint32_t command_code) {
    if (wait_mask(I2C_BASE + 16, 1, 0, 50000)) {
        return -1;
    }
    REG32(I2C_BASE + 12) = command_code;
    if (wait_mask(I2C_BASE + 16, 1, 0, 50000)) {
        return -1;
    }
    return (REG32(I2C_BASE + 16) & 2u) != 0 ? 0 : -1;
}

int i2c_read_register(uint8_t device_address,
                      uint8_t register_address,
                      uint8_t *register_value) {
    if (device_address > 127 || register_value == 0) {
        return -1;
    }

    REG32(I2C_BASE) = device_address;
    REG32(I2C_BASE + 4) = register_address;
    if (i2c_execute_command(2)) {
        return -1;
    }
    *register_value = (uint8_t)REG32(I2C_BASE + 8);
    return 0;
}

int i2c_write_register(uint8_t device_address,
                       uint8_t register_address,
                       uint8_t register_value) {
    if (device_address > 127) {
        return -1;
    }

    REG32(I2C_BASE) = device_address;
    REG32(I2C_BASE + 4) = register_address;
    REG32(I2C_BASE + 8) = register_value;
    return i2c_execute_command(1);
}

int eeprom_wait_ready(uint32_t timeout_ticks) {
    const uint64_t start_time = timer_now();
    do {
        REG32(I2C_BASE) = 0x50;
        const int address_acknowledged = i2c_execute_command(3) == 0;
        (void)i2c_execute_command(8); // STOP
        if (address_acknowledged) {
            return 0;
        }
    } while (timer_now() - start_time < timeout_ticks);
    return -1;
}

int temperature_read(int16_t *temperature_centidegrees,
                     uint16_t *humidity_centipercent) {
    uint8_t sensor_bytes[4];
    if (temperature_centidegrees == 0 || humidity_centipercent == 0) {
        return -1;
    }

    for (unsigned register_index = 0; register_index < 4; ++register_index) {
        if (i2c_read_register(0x40,
                              (uint8_t)register_index,
                              &sensor_bytes[register_index])) {
            return -1;
        }
    }

    *temperature_centidegrees = (int16_t)(
        (uint16_t)sensor_bytes[0] |
        ((uint16_t)sensor_bytes[1] << 8));
    *humidity_centipercent = (uint16_t)(
        (uint16_t)sensor_bytes[2] |
        ((uint16_t)sensor_bytes[3] << 8));
    return 0;
}

int adc_read(unsigned channel_index, uint16_t *conversion_result) {
    uint8_t status_register;
    uint8_t result_low_byte;
    uint8_t result_high_byte;

    if (channel_index > 3 || conversion_result == 0 ||
        spi_write_register(2, 3, (uint8_t)channel_index) ||
        spi_write_register(2, 1, 1)) {
        return -1;
    }

    const uint64_t start_time = timer_now();
    do {
        if (spi_read_register(2, 2, &status_register)) {
            return -1;
        }
        if (timer_now() - start_time > 10000) {
            return -1;
        }
    } while ((status_register & 2u) == 0);

    if (spi_read_register(2, 0x10, &result_low_byte) ||
        spi_read_register(2, 0x11, &result_high_byte)) {
        return -1;
    }

    *conversion_result = (uint16_t)(
        (uint16_t)result_low_byte |
        ((uint16_t)result_high_byte << 8));
    return spi_write_register(2, 2, 2); // W1C conversion-ready flag
}

int dma_copy(void *destination,
             const void *source,
             uint32_t transfer_length_bytes,
             uint32_t timeout_ticks) {
    if (wait_mask(DMA_BASE + 16, 1, 0, timeout_ticks)) {
        return -1;
    }

    REG32(DMA_BASE) = (uint32_t)(uintptr_t)source;
    REG32(DMA_BASE + 4) = (uint32_t)(uintptr_t)destination;
    REG32(DMA_BASE + 8) = transfer_length_bytes;
    REG32(DMA_BASE + 12) = 1; // START

    if (wait_mask(DMA_BASE + 16, 1, 0, timeout_ticks)) {
        REG32(DMA_BASE + 12) = 64; // ABORT
        return -1;
    }
    return (REG32(DMA_BASE + 16) & 4u) != 0 ? -1 : 0;
}
