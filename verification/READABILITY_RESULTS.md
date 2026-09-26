# 可读性重构验收记录

本轮目标不是增加新功能，而是让 MiniMCU 更适合作为教学源码阅读。

## 已完成

- `Device/Bus/MMIO` 等接口把 `a/n/v` 改成 `system_address / register_offset / access_size_bytes / write_value`。
- CPU 指令编码器保留 RISC-V I/R/S/B/U/J 标准格式名，但形参统一为 `destination_register / source_register1 / source_register2 / funct3_value / funct7_value / immediate`。
- Scheduler/Clock/Timer/UART/SPI/I²C/DMA/ELF/SoC 的地址、长度、时间、频率参数均在名称中注明语义和单位。
- Demo、测试辅助代码、裸机 C runtime/driver、FreeRTOS 示例、SystemC/TLM 入口同步采用相同命名。
- BME280/MCP23017 等芯片模型清理 `p/t/h/v` 等局部变量，并补充寄存器布局和副作用中文注释。
- RTL 端口从 `a_i/b_i/addr_i/wdata_i/rdata_o` 等缩写扩展为 `operand_a_i / operand_b_i / register_offset_i / write_data_i / read_data_o` 等语义名称。
- 新增 `rtl/tools/port_consistency_check.py`，在没有 HDL 编译器时也能检查仓库内 named-port 连接是否漏改。
- 命名与注释原则见 `docs/CODE_READABILITY_CN.md`。

## 静态扫描

- C/C++ 函数形参扫描：未发现 `a/b/n/v/len/buf/...` 等无上下文含义的短形参。
- 教学 C++ 核心中保留的单字母函数名仅有 RISC-V 官方 I/R/S/B/U/J 指令格式编码器；其输入参数均为完整语义名称。
- RTL 中已清除 `op_i/a_i/b_i/addr_i/wdata_i/wstrb_i/rdata_o/valid_i/write_i/ready_o/error_o/source_i/tx_o/code_o` 等本项目内含义模糊的端口名。
- RTL named-port 静态一致性：17 个模块检查通过。

## 编译与运行

- Release 严格告警构建：`-Werror -Wconversion -Wsign-conversion -Wshadow`，通过。
- CTest：48 项注册，47 PASS、0 FAIL、1 SKIP。唯一 SKIP 为缺少 Verilator/Icarus 的真实 RTL 动态仿真。
- ASan/UBSan：47 PASS、0 FAIL、1 SKIP，无 sanitizer 报告。
- 三套 RV32 裸机固件从 C/汇编源码重新交叉编译并运行通过：bare-metal、Machine Timer interrupt、peripheral firmware。
- FreeRTOS 与 SystemC/TLM 的真实第三方依赖在当前沙盒仍不可获得，因此相关第三方集成不能因为本轮源码可读性修改而宣称已经动态编译通过。
