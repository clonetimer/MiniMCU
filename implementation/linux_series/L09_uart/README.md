# L09 — UART MMIO Driver

从 write() 进入 UART DATA 寄存器；说明教学接口与 serial_core 的边界

## 源码入口

- `linux_drivers/src/l09_uart.c`

## 动画数据流

`Userspace write → miscdevice → MMIO DATA → UART TX`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
