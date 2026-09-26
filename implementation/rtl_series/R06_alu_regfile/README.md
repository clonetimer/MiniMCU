# R06 — ALU 与 Register File

把 RV32I 数据通路拆成 ALU、立即数生成和寄存器文件。

## 源码入口

- `rtl/core/rv32_alu.sv`
- `rtl/core/rv32_regfile.sv`
- `rtl/core/rv32_immgen.sv`

## 动画数据流

`Instruction fields → Regfile → ALU → Writeback`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
