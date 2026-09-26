# 20_event_scheduler

## 本阶段

Event scheduler。同时间稳定顺序、取消、旧 token、回调再安排事件、禁止嵌套推进。

## 源码入口

- `course/03_system_software/20_event_scheduler/main.cpp`：独立可执行入口。
- `core/sim.hpp`：共享实现；各阶段不复制历史版本核心。
- `tests/lessons.cpp 的 stage 20 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/03_system_software/20_event_scheduler -B build-20 -DCMAKE_BUILD_TYPE=Release
cmake --build build-20 --parallel 4
./build-20/bin/20_event_scheduler
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-20/bin/20_event_scheduler --trace
ctest --test-dir build-20 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

下一阶段：`course/03_system_software/21_clock_reset`。
