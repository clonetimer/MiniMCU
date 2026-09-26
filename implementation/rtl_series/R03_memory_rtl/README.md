# R03 — RAM / ROM RTL

理解 byte strobe、小端序、同步写和 ROM 初始化。

## 源码入口

- `rtl/memory/simple_ram.sv`
- `rtl/memory/simple_rom.sv`

## 动画数据流

`Bus request → Byte strobes → Memory array → Read response`

## 验证

- `python3 rtl/tools/series_check.py`：课程源文件、模块与映射结构检查。
- `python3 rtl/tools/run_rtl_tests.py`：检测到 Icarus/Verilator 后执行真实 HDL testbench；无模拟器时返回 77（SKIP）。
