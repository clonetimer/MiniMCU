# L13 — Device Tree / Binding

从 DTS reg/interrupts/compatible 到驱动 probe

## 源码入口

- `linux_drivers/dts/minimcu-linux-lab.dts`
- `linux_drivers/bindings/openai,minimcu-gpio.yaml`

## 动画数据流

`DTS → DTB concept → OF match → probe resources`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
