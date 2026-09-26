# R11 — C++ ↔ RTL Differential 接口

利用 retire stream 建立 C++ golden model 与 RTL DUT 的逐退休比较接口。

## 源码入口

- `rtl/soc/minimcu_soc.sv`
- `rtl/tools/run_rtl_tests.py`

## 动画数据流

`C++ reference → Program → RTL retire stream → Comparator`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
