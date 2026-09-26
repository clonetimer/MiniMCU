# L15 — 综合平台驱动

组合 Device Tree、MMIO、IRQ 与 sysfs，形成完整 probe→runtime→remove 生命周期

## 源码入口

- `linux_drivers/src/l15_integrated.c`

## 动画数据流

`Device Tree → probe/resources → MMIO + IRQ → sysfs/runtime`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
