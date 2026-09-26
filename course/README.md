# Course：01–46 主线 + 47–54 可选通信协议轨

这里是学生最主要的入口。目录顺序就是推荐学习顺序。

```text
course/
├── 01_foundations/       01–04  最小计算机组成
├── 02_cpu_rv32i/         05–16  RV32I CPU
├── 03_system_software/   17–26  裸机与异常/中断系统
├── 04_peripherals/       27–36  MCU 常用外设
├── 05_integration/       37–42  RTOS/DMA/具体芯片
├── 06_modeling/          43–46  SystemC/TLM/虚拟芯片
├── 07_protocols/         47–54  通信协议轨 + 可选高级 Lab
└── guide/                专题导航索引
```

## 每章怎么看

每个 `NN_topic/` 目录尽量保持很薄：

- `README.md`：本章目的和对应源码；
- `main.cpp`：本章演示入口；
- `CMakeLists.txt`：本章独立构建入口；
- 个别综合章节还会包含本章专属 firmware。

真正可复用实现集中在 `core/`，因此推荐：

```text
章节 main.cpp → 找到使用的类 → 到 core/README.md 定位实现文件
```

## 单独构建某一章

例如只学习 SPI Controller：

```bash
cmake -S course/04_peripherals/29_spi_controller -B build-stage29 -DCMAKE_BUILD_TYPE=Release
cmake --build build-stage29
ctest --test-dir build-stage29 --output-on-failure
```

这可以避免初学阶段一次构建整个仓库。

## 可选通信协议轨 47–54

完成 01–46 后，如果学习方向偏嵌入式通信，再进入 `07_protocols/`。根工程默认不构建它：

```bash
cmake -S . -B build-protocols -DMINICPU_BUILD_PROTOCOL_TRACK=ON
cmake --build build-protocols --parallel 4
ctest --test-dir build-protocols --output-on-failure
```

47–54 不改变 01–46 的编号和学习顺序。完成对应协议章节后，可再用 `-DMINICPU_BUILD_PROTOCOL_LABS=ON` 开启 `labs/`；Lab 没有新增章节编号。
