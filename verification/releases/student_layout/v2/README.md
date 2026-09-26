# Student Layout V2 verification

本目录保存 Student Layout V2 / Protocol Track 47–54 的验证摘要。

- `ctest.txt`：开启 Protocol Track 后的完整默认回归；
- `strict_warnings.txt`：47–54 与统一协议回归在 `-Werror` 下通过；
- `sanitizer.txt`：47–54 与统一协议回归在 ASan/UBSan 下通过；
- `standalone_stages.txt`：8 个章节独立配置/构建/测试；
- `default_build_policy.txt`：默认根构建没有 47–54 目标/测试；
- `behavior_source_check.txt`：V1 既有行为源码逐文件 SHA256 不变；
- `changes.sha256`：本版本新增/修改的 Student Layout V2 内容校验。
