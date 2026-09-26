# L12 — Linux DMA API

区分 CPU virtual address 与 dma_addr_t，并建立 coherent buffer

## 源码入口

- `linux_drivers/src/l12_dma.c`

## 动画数据流

`Driver → dma_alloc_coherent → DMA address → Device`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
