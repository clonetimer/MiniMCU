# R09 — CSR / Trap / Interrupt

在 RTL 中建立 mepc/mcause/mtvec 与 mret 的异常控制路径。

## 源码入口

- `rtl/core/rv32_core.sv`
- `rtl/peripherals/machine_timer.sv`
- `rtl/peripherals/interrupt_controller.sv`

## 动画数据流

`IRQ source → CSR gate → Trap entry → MRET`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
