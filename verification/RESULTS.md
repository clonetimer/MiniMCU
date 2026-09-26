# 实际命令执行记录

UTC: 2026-09-14T16:07:28.416305+00:00
状态：**PASS_FOR_REQUESTED_CONFIGURATION**

FreeRTOS 请求构建/测试：False；SystemC 请求构建/测试：False。
未请求的阶段不属于本记录的通过结论。

| 命令 | 退出码 | 日志 |
|---|---:|---|
| firmware-baremetal | 0 | `verification/latest/firmware-baremetal.log` |
| firmware-interrupt | 0 | `verification/latest/firmware-interrupt.log` |
| firmware-peripherals | 0 | `verification/latest/firmware-peripherals.log` |
| configure | 0 | `verification/latest/configure.log` |
| build | 0 | `verification/latest/build.log` |
| test-inventory | 0 | `verification/latest/test-inventory.log` |
| ctest | 0 | `verification/latest/ctest.log` |

完整参数、测试清单和 ELF SHA-256 见 `latest/result.json`。命令通过不等于 RISC-V 认证，也不覆盖未启用的依赖阶段。
