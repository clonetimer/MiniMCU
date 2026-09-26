# Demo / Trace 分离修订验收

本文件记录本轮“阶段 Demo + `--trace` + 独立 CTest”改造的实际沙盒结果。

## 已执行结果

- Release 根工程：使用 GCC，额外 `-Werror`，配置与全量编译成功，编译日志 0 warning。
- 严格转换检查：Clang 全工程增加 `-Wconversion -Wsign-conversion -Wshadow -Wimplicit-int-conversion -Wconstant-conversion`，0 warning。
- 阶段默认 Demo：01–42、46 共 43 个程序全部退出 0。
- 阶段 Trace：01–42、46 共 43 个程序使用 `--trace` 全部退出 0。
- 单独阶段构建：01 和 06 分别使用自己的 `CMakeLists.txt` 从零配置、构建、Demo、CTest 通过。
- CTest：48 项注册，47 PASS、0 FAIL、1 SKIP。唯一 SKIP 是当前沙盒缺少 Verilator/Icarus 的 `rtl_simulation`。
- ASan/UBSan：同样 47 PASS、0 FAIL、1 SKIP，无 sanitizer 报告。
- RISC-V 固件从 C/汇编重新交叉编译：bare-metal、Machine Timer interrupt、peripheral firmware 均在 MiniMCU 上实际运行通过。

## 行为变化

阶段 executable 不再调用 `lessons::run()`。

```text
01_gpio_rw32.exe          -> 教学 Demo
06_cpu_addi.exe --trace   -> 详细 CPU/Bus Trace
ctest                     -> 独立自动验收
```

CPU Trace 显示 PC、机器指令、反汇编、源寄存器、writeback、next PC、trap 与实际 Bus transaction。外设 Demo 根据阶段显示 UART 时间、SPI/I2C transaction、DMA backpressure、事件时间等。

## MSVC 日志对应修复

针对用户在 Visual Studio `/W4` 下观察到的 C4310/C4244/C4245 源头，已处理：

- SPI ADC 3300mV 常量分拆时的显式 8-bit 窄化；
- ADS1115 reset 中不同宽度变量的连写赋值；
- `Memory::reset()` 与 ELF BSS 清零明确传入 `uint8_t{0}`；
- RV32 I/S/B/J encoder 的 immediate 参数改为 `int64_t`，避免负 immediate 先隐式转无符号；
- 8/16-bit 数据拼接增加显式类型转换。

当前沙盒没有 MSVC，因此不能声称实际执行了 `cl.exe /W4`；严格 Clang 转换告警构建作为补充证据。
