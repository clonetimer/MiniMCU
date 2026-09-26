# 37_freertos

## 本阶段

Real FreeRTOS integration。真实上游 kernel/port、两个不主动 yield 的 worker、30 tick 后检验抢占和栈。

## 源码入口

- `course/05_integration/37_freertos/main.cpp`：独立可执行入口。
- `core/cpu.hpp`：共享实现；各阶段不复制历史版本核心。
- `course/05_integration/37_freertos/firmware/、tools/build_freertos.py 与 tests/lessons.cpp 的 stage 37 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/05_integration/37_freertos -B build-37 -DCMAKE_BUILD_TYPE=Release
cmake --build build-37 --parallel 4
./build-37/bin/37_freertos
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-37/bin/37_freertos --trace
ctest --test-dir build-37 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

默认只构建宿主 runner。必须获取真实 FreeRTOS V11.2.0 源码并交叉编译固件；建议使用根目录 `-DMINICPU_WITH_FREERTOS=ON` 构建。没有 ELF 时 runner 报错，绝不使用模拟替代调度器。

下一阶段：`course/05_integration/38_dma_mem2mem`。
