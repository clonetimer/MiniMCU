# MiniMCU RTL Series R01–R12

本系列不改写 Core/Advanced 的 C++ 行为。已有 `rtl/` 是独立手写 SystemVerilog 实现；R 系列把它组织成循序课程，并补充 reset synchronizer、wait-state target、round-robin arbiter 和 FPGA top。

当前环境没有 Icarus/Verilator/Yosys，因此包内区分两种验证：依赖无关的 source-map/structure check 可以实际执行；HDL compile/simulation 仅在工具存在时自动执行。
