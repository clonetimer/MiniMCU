# L11 — SPI Protocol Driver

用 spi_driver 和 spi_write_then_read 访问 IMU 风格设备

## 源码入口

- `linux_drivers/src/l11_spi.c`

## 动画数据流

`Device Tree → SPI core → spi_driver → IMU`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
