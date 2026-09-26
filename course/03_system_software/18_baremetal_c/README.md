# 18_baremetal_c

## 本阶段

Bare-metal C。加载真正交叉编译的 C ELF，验证启动、数据段、BSS、函数调用和 UART。

## 源码入口

- `course/03_system_software/18_baremetal_c/main.cpp`：独立可执行入口。
- `core/elf.hpp`：共享实现；各阶段不复制历史版本核心。
- `tests/lessons.cpp 的 stage 18 分支`：验收逻辑。


## 运行模式

- 直接运行本阶段可执行文件：教学 Demo，输出本阶段的关键状态和结果。
- 增加 `--trace`：输出更详细的 CPU/Bus/协议过程。
- `ctest`：运行独立自动验收，测试逻辑与 Demo 输出分离。

## 构建与运行

在项目根目录执行：

```sh
cmake -S course/03_system_software/18_baremetal_c -B build-18 -DCMAKE_BUILD_TYPE=Release
cmake --build build-18 --parallel 4
./build-18/bin/18_baremetal_c
```

直接运行阶段程序会输出教学 Demo；增加 `--trace` 可查看更详细的内部过程。自动 PASS/FAIL 验收由独立 CTest 入口执行：

```sh
./build-18/bin/18_baremetal_c --trace
ctest --test-dir build-18 --output-on-failure
```

Windows 多配置生成器在构建/CTest 时使用 `--config Release` / `-C Release`。

运行前需要 `firmware/prebuilt/baremetal.elf`；重建命令见根 README，也可给可执行文件传入另一个 ELF 路径。

下一阶段：`course/03_system_software/19_cpu_mmio_gpio`。
