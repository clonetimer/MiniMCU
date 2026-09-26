# 39_dma_peripheral

## 本阶段

DMA peripheral handshake。TX FIFO 背压和 RX request；等待时无轮询事件，输入到达后继续。

## 源码入口

- `course/05_integration/39_dma_peripheral/main.cpp`：独立可执行入口。
- `core/dma.hpp`：共享实现；各阶段不复制历史版本核心。
- `tests/lessons.cpp 的 stage 39 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/05_integration/39_dma_peripheral -B build-39 -DCMAKE_BUILD_TYPE=Release
cmake --build build-39 --parallel 4
./build-39/bin/39_dma_peripheral
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-39/bin/39_dma_peripheral --trace
ctest --test-dir build-39 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

下一阶段：`course/05_integration/40_spi_imu`。
