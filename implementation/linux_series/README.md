# MiniMCU Linux Driver Series L01–L15

目标不是让冻结的 MiniMCU Core 直接启动 Linux，而是在标准 Linux 内核驱动模型中复用 MiniMCU 的 MMIO/IRQ/I²C/SPI/DMA 概念。

源码位于 `linux_drivers/`。L01–L12/L14/L15 是可编译 kernel module；L13 是 DTS/binding。
