# L06 — ioctl ABI

理解用户态控制命令、copy_to/from_user 和 ABI 边界

## 源码入口

- `linux_drivers/src/l06_ioctl.c`

## 动画数据流

`Userspace ioctl → VFS → unlocked_ioctl → Kernel state`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
