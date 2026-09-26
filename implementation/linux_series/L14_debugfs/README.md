# L14 — debugfs Diagnostics

用 debugfs 暴露仅用于调试的内核状态，区分稳定 ABI

## 源码入口

- `linux_drivers/src/l14_debugfs.c`

## 动画数据流

`Driver state → debugfs → VFS → Developer`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
