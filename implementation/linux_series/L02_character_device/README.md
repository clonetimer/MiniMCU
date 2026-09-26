# L02 — Character Device

用 miscdevice 建立 /dev 接口和 read/write 数据路径

## 源码入口

- `linux_drivers/src/l02_chardev.c`

## 动画数据流

`Userspace → VFS → file_operations → Driver state`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
