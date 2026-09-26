# MiniMCU：学生从这里开始

第一次打开仓库时，只需要先认识四个目录：

```text
course/      01–46 核心课程；47–54 是完成主线后的可选通信协议轨
core/        C++ 模拟器/SoC 的核心实现
firmware/    裸机 C 固件与预编译 ELF
tests/       跨章节回归与行为测试
```

其余目录先不用看。`advanced/`、`fpga/`、`dsp/`、`implementation/`、`linux_drivers/`、`extensions/` 都是可选专题或高级扩展。

## 0. 第一次打开源码：先做 15 分钟主线 Guided Demo

如果还没有形成 MCU / Bus / MMIO 的心智模型，先不要从 54 个章节目录开始。打开：

```text
learning_demo/index.html
```

或：

```bash
cd learning_demo
./start_demo.sh
```

Demo 会先给你一块真实风格的教学开发板，再引导你完成 `板上 LED/Pin ↔ DIR/OUTPUT/PIN → 芯片内部 Bus 地址译码 → CPU MMIO → SPI/I2C/CAN 实际连线 → 源码路线`。主线完成后，可以选做两个 Side Quest：`Scheduler / simulated time` 与 `IRQ / Interrupt / Trap`。

它使用矢量教学板而不是某一块商业开发板照片，但 pin、PCB trace、LED、button、sensor、transceiver 都对应真实概念。它只负责建立第一张地图，不替代章节和 CTest；Side Quest 也不是新手必做。

## 1. 学习入口

先进入：

```text
course/README.md
```

主线按六个阶段组织：

```text
course/
├── 01_foundations/       GPIO / RAM / Bus / ROM
├── 02_cpu_rv32i/         从 Fetch 到完整 RV32I
├── 03_system_software/   ELF / 裸机 C / CSR / Trap / Interrupt
├── 04_peripherals/       UART / SPI / I2C / Timer / GPIO IRQ
├── 05_integration/       FreeRTOS / DMA / 具体器件
├── 06_modeling/          SystemC / TLM / Virtual Chips
└── 07_protocols/         47–54 通信协议 + labs/ 选做高级实验（默认不构建）
```

章节编号仍然是稳定索引，例如：

```text
course/04_peripherals/29_spi_controller/
```

对应可执行文件名称仍然是：

```text
29_spi_controller
```

## 2. 最小构建流程

### Linux / macOS

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
./build/bin/01_gpio_rw32
./build/bin/06_cpu_addi --trace
ctest --test-dir build --output-on-failure
```

### Windows PowerShell

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\bin\01_gpio_rw32.exe
.\build\bin\06_cpu_addi.exe --trace
ctest --test-dir build -C Release --output-on-failure
```

## 3. 读源码的顺序

每个章节建议固定采用：

```text
本章 README
   ↓
main.cpp（只看本章想展示什么）
   ↓
core/ 中对应实现
   ↓
--trace / CTest 验证
   ↓
自己修改并重新运行
```

不要一开始直接通读 `core/chips.hpp` 或整个 SoC。

核心实现的推荐阅读顺序见：

```text
core/README.md
```

完整目录职责图见：

```text
docs/STUDENT_SOURCE_MAP.md
```

## 4. 高级内容什么时候看

完成 01–46 主线后，可以先进入 `course/07_protocols/` 学 MCU 通信协议扩展；再按需要进入：

- `advanced/`：Debug、验证、Boot、可靠性、Cache/互连等高级专题；
- `rtl/`：SystemVerilog 实现与 RTL 仿真；
- `fpga/` / `dsp/`：FPGA 与 DSP 专题；
- `linux_drivers/`：Linux 驱动课程；
- `extensions/system_fidelity_v*/`：System Fidelity 系统级事务/并发总线扩展。

这些目录不会参与“从零开始”的阅读顺序。

通信协议轨启用方式：`-DMINICPU_BUILD_PROTOCOL_TRACK=ON`；完成对应章节后，用 `-DMINICPU_BUILD_PROTOCOL_LABS=ON` 再进入选做 Lab。学习 47–54 时建议先看 `course/07_protocols/TEACHING_REVIEW.md`，它说明每章只应该掌握一个核心问题。其他专题构建开关统一见 `docs/OPTIONAL_TOPICS.md`。


## Workbench V2

The optional first protocol schematic is documented in [`WORKBENCH_V2_START_HERE.md`](WORKBENCH_V2_START_HERE.md). Workbench V1 remains available unchanged.
