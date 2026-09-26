# L05 — GPIO Subsystem

把 MiniMCU GPIO 接入 Linux gpio_chip 框架

## 源码入口

- `linux_drivers/src/l05_gpiochip.c`

## 动画数据流

`GPIO consumer → gpiolib → gpio_chip callbacks → MiniMCU GPIO`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
