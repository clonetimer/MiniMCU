# 37–42：系统集成

把 CPU、DMA、RTOS 和具体外部芯片组合起来。

| 章节 | 内容 |
|---|---|
| [`37_freertos/`](37_freertos/) | FreeRTOS |
| [`38_dma_mem2mem/`](38_dma_mem2mem/) | DMA Mem2Mem |
| [`39_dma_peripheral/`](39_dma_peripheral/) | DMA + Peripheral |
| [`40_spi_imu/`](40_spi_imu/) | SPI IMU |
| [`41_i2c_eeprom/`](41_i2c_eeprom/) | I2C EEPROM |
| [`42_adc/`](42_adc/) | ADC |

## 阅读建议

先运行本阶段最前面的章节，再看 `main.cpp` 使用了哪些 `core/` 类型；不要先从核心实现反向猜课程目标。
