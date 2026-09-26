#ifndef MINICPU_DRIVERS_H
#define MINICPU_DRIVERS_H

#include "platform.h"

#define SPI_BASE 0x40003000u
#define I2C_BASE 0x40004000u
#define IRQ_BASE 0x0c000000u
#define DMA_BASE 0x40006000u
#define GPT_BASE 0x40005000u

void gpio_configure(uint32_t output_mask);
void gpio_set(uint32_t pin_mask);
void gpio_clear(uint32_t pin_mask);
void gpio_irq_configure(uint32_t rising_edge_mask,
                        uint32_t falling_edge_mask,
                        uint32_t interrupt_enable_mask);
void gpio_irq_clear(uint32_t pending_mask);

void irq_configure(unsigned source_id,
                   unsigned priority,
                   int enable_source);
unsigned irq_claim(void);
void irq_complete(unsigned source_id);

int spi_select(int chip_select_id);
int spi_transfer(uint8_t transmitted_byte,
                 uint8_t *received_byte,
                 uint32_t timeout_ticks);
int spi_read_register(unsigned chip_select_id,
                      uint8_t register_address,
                      uint8_t *register_value);
int spi_write_register(unsigned chip_select_id,
                       uint8_t register_address,
                       uint8_t register_value);

int flash_id(uint8_t jedec_id[3]);
int flash_program_byte(uint32_t flash_address, uint8_t byte_value);
int flash_read_byte(uint32_t flash_address, uint8_t *byte_value);

int i2c_read_register(uint8_t device_address,
                      uint8_t register_address,
                      uint8_t *register_value);
int i2c_write_register(uint8_t device_address,
                       uint8_t register_address,
                       uint8_t register_value);
int eeprom_wait_ready(uint32_t timeout_ticks);
int temperature_read(int16_t *temperature_centidegrees,
                     uint16_t *humidity_centipercent);
int adc_read(unsigned channel_index, uint16_t *conversion_result);

int dma_copy(void *destination,
             const void *source,
             uint32_t transfer_length_bytes,
             uint32_t timeout_ticks);

#endif
