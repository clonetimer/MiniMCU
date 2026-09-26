# 30_spi_bus

## 本阶段

SPI bus。CS 多设备连接、选择边沿、未选设备返回0xff、重复连接错误。

## 源码入口

- `course/04_peripherals/30_spi_bus/main.cpp`：独立可执行入口。
- `core/spi.hpp`：共享实现；各阶段不复制历史版本核心。
- `tests/lessons.cpp 的 stage 30 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/04_peripherals/30_spi_bus -B build-30 -DCMAKE_BUILD_TYPE=Release
cmake --build build-30 --parallel 4
./build-30/bin/30_spi_bus
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-30/bin/30_spi_bus --trace
ctest --test-dir build-30 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

下一阶段：`course/04_peripherals/31_spi_flash`。
