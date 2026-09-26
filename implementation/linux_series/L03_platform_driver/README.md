# L03 — Platform Device / Driver

理解 Device Tree、platform_device 与 probe 的匹配关系

## 源码入口

- `linux_drivers/src/l03_platform.c`

## 动画数据流

`Device Tree → OF match → platform bus → probe`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
