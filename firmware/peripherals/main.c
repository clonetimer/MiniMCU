#include "drivers.h"

static uint8_t dma_source_buffer[64];
static uint8_t dma_destination_buffer[64];

int main(void) {
    uint8_t flash_jedec_id[3];
    uint8_t register_value;
    int16_t temperature_centidegrees;
    uint16_t humidity_centipercent;
    uint16_t adc_conversion_result;

    /* SPI Flash：读取 JEDEC ID。 */
    if (flash_id(flash_jedec_id) != 0 ||
        flash_jedec_id[0] != 0xef ||
        flash_jedec_id[1] != 0x40 ||
        flash_jedec_id[2] != 0x14) {
        return 40;
    }

    /* SPI Flash：编程一个字节后再读回。 */
    if (flash_program_byte(0x123, 0xa5) != 0 ||
        flash_read_byte(0x123, &register_value) != 0 ||
        register_value != 0xa5) {
        return 41;
    }

    /* SPI IMU：读取 WHO_AM_I/ID 寄存器。 */
    if (spi_read_register(1, 0, &register_value) != 0 ||
        register_value != 0x42) {
        return 42;
    }

    /* I²C 温湿度传感器：默认环境为 23.50 °C / 50.00 %RH。 */
    if (temperature_read(&temperature_centidegrees,
                         &humidity_centipercent) != 0 ||
        temperature_centidegrees != 2350 ||
        humidity_centipercent != 5000) {
        return 43;
    }

    /* I²C EEPROM：写入后等待内部写周期完成，再读回验证。 */
    if (i2c_write_register(0x50, 7, 0x69) != 0 ||
        eeprom_wait_ready(20000) != 0 ||
        i2c_read_register(0x50, 7, &register_value) != 0 ||
        register_value != 0x69) {
        return 44;
    }

    /* 默认模拟环境的 ADC 通道输入为 0 mV。 */
    if (adc_read(0, &adc_conversion_result) != 0 ||
        adc_conversion_result != 0) {
        return 45;
    }

    for (unsigned byte_index = 0;
         byte_index < sizeof(dma_source_buffer);
         ++byte_index) {
        dma_source_buffer[byte_index] = (uint8_t)(byte_index ^ 0xa5U);
    }

    if (dma_copy(dma_destination_buffer,
                 dma_source_buffer,
                 sizeof(dma_source_buffer),
                 10000) != 0) {
        return 46;
    }

    for (unsigned byte_index = 0;
         byte_index < sizeof(dma_source_buffer);
         ++byte_index) {
        if (dma_destination_buffer[byte_index] !=
            dma_source_buffer[byte_index]) {
            return 47;
        }
    }

    uart_puts("peripheral C: PASS (Flash/IMU/I2C/EEPROM/ADC/DMA)\n");
    return 0;
}
