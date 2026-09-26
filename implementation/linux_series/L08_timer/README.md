# L08 — Timer Driver

结合 MMIO 和 IRQ 驱动 MiniMCU 风格 timer

## 源码入口

- `linux_drivers/src/l08_timer.c`

## 动画数据流

`Timer registers → Comparator → IRQ → Driver tick`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
