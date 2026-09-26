# 17–26：系统软件与异常

把 CPU 从“执行指令”推进到“可以运行裸机程序并处理时间、异常和中断”。

| 章节 | 内容 |
|---|---|
| [`17_elf_loader/`](17_elf_loader/) | ELF 加载 |
| [`18_baremetal_c/`](18_baremetal_c/) | 裸机 C |
| [`19_cpu_mmio_gpio/`](19_cpu_mmio_gpio/) | CPU + MMIO |
| [`20_event_scheduler/`](20_event_scheduler/) | 事件调度 |
| [`21_clock_reset/`](21_clock_reset/) | Clock/Reset |
| [`22_zicsr/`](22_zicsr/) | CSR |
| [`23_exception_trap/`](23_exception_trap/) | Exception/Trap |
| [`24_machine_timer/`](24_machine_timer/) | 机器定时器 |
| [`25_interrupt/`](25_interrupt/) | Interrupt |
| [`26_interrupt_controller/`](26_interrupt_controller/) | 中断控制器 |

## 阅读建议

先运行本阶段最前面的章节，再看 `main.cpp` 使用了哪些 `core/` 类型；不要先从核心实现反向猜课程目标。
