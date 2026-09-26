# R12 — FPGA SoC Bring-up

把 SoC 包装成板级 top，连接 reset、switch、LED 与 UART。

## 源码入口

- `rtl/fpga/minimcu_fpga_top.sv`
- `rtl/soc/minimcu_soc.sv`

## 动画数据流

`Board clock/reset → MiniMCU SoC → GPIO/UART → FPGA pins`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
