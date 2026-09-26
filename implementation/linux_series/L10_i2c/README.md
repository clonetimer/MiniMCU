# L10 — I²C Client Driver

用 i2c_driver/SMBus API 驱动一个枚举的传感器客户端

## 源码入口

- `linux_drivers/src/l10_i2c.c`

## 动画数据流

`Device Tree → I2C core → i2c_driver → Sensor`

## 验证边界

本包在可用 Debian Linux headers 上执行真实 out-of-tree module compilation；由于当前环境没有 QEMU/可绑定的 MiniMCU Linux 设备，本次不声称 probe/IRQ/DMA 运行态已经执行。
