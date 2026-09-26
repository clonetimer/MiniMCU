# L07 — Linux IRQ

从 platform_get_irq 到 devm_request_irq 与 ISR

## 源码入口

- `linux_drivers/src/l07_irq.c`

## 动画数据流

`Device IRQ → IRQ core → ISR → Driver state`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
