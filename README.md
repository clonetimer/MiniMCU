# MiniMCU Workbench V2.0.1

> 面向教学的微型 MCU / SoC 模拟器与 RV32I 课程体系。本仓库是 **Workbench V2.0.1** 的源码快照。

## 简介

MiniMCU 通过一块矢量教学开发板与从零构建的 C++ 模拟器，帮助学生建立
「GPIO / Bus / MMIO / CPU / 外设 / 系统软件」的完整心智模型，并配套 RV32I 主线课程
（从 Fetch 到完整 RV32I、系统软件、外设、集成）以及可选的通信协议轨。

## 本仓库内容

| 目录 / 文件 | 说明 |
|------|------|
| `course/` | RV32I 主线实验：`02_cpu_rv32i`、`03_system_software`、`04_peripherals`、`05_integration`；每章含 `README.md` + `main.cpp` |
| `firmware/` | 裸机 C 固件与预编译 ELF |
| `implementation/` | 核心实现专题：`linux_series/`、`rtl_series/` |
| `verification/` | 跨版本回归、严格警告、Sanitizer、发布校验等验证证据 |
| `README_START_HERE.md` | **学生入口**：15 分钟主线 Guided Demo 与六个阶段学习路线 |
| `APP_V2_START_HERE.md` | App V2（调试器聚焦）说明与构建 |

> 注：这是 Workbench V2.0.1 的子集快照。完整目录（`core/`、`tests/`、`advanced/`、`rtl/`、`fpga/` 等）
> 与全局阅读顺序以 `README_START_HERE.md` 中的说明为准。

## 快速开始

### Linux / macOS

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
./build/bin/01_gpio_rw32
./build/bin/06_cpu_addi --trace
ctest --test-dir build --output-on-failure
```

### Windows (PowerShell)

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\bin\01_gpio_rw32.exe
.\build\bin\06_cpu_addi.exe --trace
ctest --test-dir build -C Release --output-on-failure
```

## 学习入口

1. 先读 `README_START_HERE.md` —— 15 分钟主线 Guided Demo 与六个阶段学习路线。
2. 进入 `course/README.md` 查看章节索引（例如 `course/04_peripherals/29_spi_controller/`）。
3. 推荐阅读顺序：本章 README → `main.cpp` → 对应实现 → `--trace` / CTest 验证 → 自行修改重跑。
4. 调试器相关（RV32I/Zicsr 反汇编、内存 peek、PC 断点等）见 `APP_V2_START_HERE.md`。

## 许可

仓库内如含 `LICENSE` 文件，以该文件为准。

---

*本 `README.md` 由自动化上传流程补充；项目原始学习说明以 `README_START_HERE.md` / `APP_V2_START_HERE.md` 为准。*
