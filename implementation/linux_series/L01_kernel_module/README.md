# L01 — Kernel Module 生命周期

理解 module_init/module_exit 与内核模块装卸边界

## 源码入口

- `linux_drivers/src/l01_hello.c`

## 动画数据流

`insmod → module_init → kernel log → rmmod`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
