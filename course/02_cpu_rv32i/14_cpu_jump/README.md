# 14_cpu_jump

## 本阶段

JAL and JALR。返回地址、rs1/rd 别名、bit0 清除、4字节对齐异常。

## 源码入口

- `course/02_cpu_rv32i/14_cpu_jump/main.cpp`：独立可执行入口。
- `core/cpu.hpp`：共享实现；各阶段不复制历史版本核心。
- `tests/lessons.cpp 的 cpu_basics 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/02_cpu_rv32i/14_cpu_jump -B build-14 -DCMAKE_BUILD_TYPE=Release
cmake --build build-14 --parallel 4
./build-14/bin/14_cpu_jump
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-14/bin/14_cpu_jump --trace
ctest --test-dir build-14 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

下一阶段：`course/02_cpu_rv32i/15_cpu_rv32i_system`。
