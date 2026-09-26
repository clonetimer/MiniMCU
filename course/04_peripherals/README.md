# 27–36：MCU 外设

按 UART → SPI → I2C → IRQ/Timer 的顺序理解外设控制器、总线与设备。

| 章节 | 内容 |
|---|---|
| [`27_uart/`](27_uart/) | UART 寄存器 |
| [`28_uart_terminal/`](28_uart_terminal/) | 终端连接 |
| [`29_spi_controller/`](29_spi_controller/) | SPI Controller |
| [`30_spi_bus/`](30_spi_bus/) | SPI Bus/Device |
| [`31_spi_flash/`](31_spi_flash/) | SPI Flash |
| [`32_i2c_controller/`](32_i2c_controller/) | I2C Controller |
| [`33_i2c_bus/`](33_i2c_bus/) | I2C Bus/Device |
| [`34_i2c_sensor/`](34_i2c_sensor/) | I2C Sensor |
| [`35_gpio_interrupt/`](35_gpio_interrupt/) | GPIO IRQ |
| [`36_general_timer/`](36_general_timer/) | General Timer |

## 阅读建议

先运行本阶段最前面的章节，再看 `main.cpp` 使用了哪些 `core/` 类型；不要先从核心实现反向猜课程目标。
