# L04 — MMIO / ioremap / readl / writel

把 MiniMCU 寄存器映射成 Linux 驱动可访问的 MMIO

## 源码入口

- `linux_drivers/src/l04_mmio.c`
- `linux_drivers/include/minimcu_regs.h`

## 动画数据流

`reg resource → ioremap → readl/writel → Device register`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
