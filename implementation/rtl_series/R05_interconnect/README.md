# R05 — 地址译码与仲裁

理解地址译码与多 Master round-robin 仲裁之间的职责边界。

## 源码入口

- `rtl/bus/minicpu_interconnect.sv`
- `rtl/advanced/rr_arbiter.sv`

## 动画数据流

`Masters → Arbiter → Address decoder → Target`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
