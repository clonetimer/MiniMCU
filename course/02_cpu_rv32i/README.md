# 05–16：RV32I CPU

从取指开始，逐步加入译码、ALU、访存、分支、跳转和 SYSTEM 指令。

| 章节 | 内容 |
|---|---|
| [`05_cpu_fetch/`](05_cpu_fetch/) | Fetch |
| [`06_cpu_addi/`](06_cpu_addi/) | ADDI 基线 |
| [`07_cpu_decode_refactor/`](07_cpu_decode_refactor/) | Decode/Immediate |
| [`08_cpu_op_imm/`](08_cpu_op_imm/) | OP-IMM |
| [`09_cpu_op/`](09_cpu_op/) | OP |
| [`10_cpu_lui_auipc/`](10_cpu_lui_auipc/) | LUI/AUIPC |
| [`11_cpu_load/`](11_cpu_load/) | LOAD |
| [`12_cpu_store/`](12_cpu_store/) | STORE |
| [`13_cpu_branch/`](13_cpu_branch/) | BRANCH |
| [`14_cpu_jump/`](14_cpu_jump/) | JAL/JALR |
| [`15_cpu_rv32i_system/`](15_cpu_rv32i_system/) | SYSTEM |
| [`16_cpu_rv32i_complete/`](16_cpu_rv32i_complete/) | 完整 RV32I 里程碑 |

## 阅读建议

先运行本阶段最前面的章节，再看 `main.cpp` 使用了哪些 `core/` 类型；不要先从核心实现反向猜课程目标。
