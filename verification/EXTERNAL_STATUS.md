# FreeRTOS / SystemC 可用性检查

本文件记录本次沙盒中的**实际可用性边界**，不把缺少第三方依赖解释为集成通过。

## FreeRTOS

- 工程的真实集成入口要求上游 `FreeRTOS-Kernel V11.2.0`，不是自制调度器替代品。
- `-DMINICPU_WITH_FREERTOS=ON` 已实际执行配置检查；由于沙盒内没有 `FreeRTOS-Kernel` 源码，CMake 按设计停止。日志：`external/freertos-config.log`。
- `tools/fetch_dependencies.py freertos` 已实际尝试；沙盒不能解析/访问 GitHub，因此无法在本环境取得内核源码。日志：`external/fetch-freertos.log`。
- 结论：**UNVERIFIED_MISSING_DEPENDENCY**。这不是“FreeRTOS 已通过”，也不是已观察到的 MiniCPU/FreeRTOS 编译错误。

## SystemC / TLM

- 43–45 使用真实 SystemC/TLM API，不提供假 `systemc` shim。
- `-DMINICPU_WITH_SYSTEMC=ON` 已实际执行配置检查；本沙盒既无 SystemC 源码也无已安装 SystemC CMake package/library，CMake 按设计停止。日志：`external/systemc-config.log`。
- `tools/fetch_dependencies.py systemc` 也因沙盒外网限制不能访问 GitHub。日志：`external/fetch-systemc.log`。
- 结论：**UNVERIFIED_MISSING_DEPENDENCY**。

## 在有依赖的环境继续验收

```bash
python3 tools/fetch_dependencies.py all
cmake -S . -B build-all \
  -DCMAKE_BUILD_TYPE=Release \
  -DMINICPU_WITH_FREERTOS=ON \
  -DMINICPU_WITH_SYSTEMC=ON
cmake --build build-all --parallel
ctest --test-dir build-all --output-on-failure
```

也可以不用联网脚本，分别通过 `MINICPU_FREERTOS_KERNEL` 和 `MINICPU_SYSTEMC_SOURCE` 指向本地真实源码。
