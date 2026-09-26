# R10 — UART / Timer 外设 RTL

把 UART 与 machine timer 作为独立 MMIO target 接入 SoC。

## 源码入口

- `rtl/peripherals/uart.sv`
- `rtl/peripherals/machine_timer.sv`
- `rtl/soc/minimcu_soc.sv`

## 动画数据流

`CPU MMIO → Interconnect → UART/Timer → External signal`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
