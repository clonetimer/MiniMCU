# Frozen baseline policy

Implementation V1 不修改已冻结课程的实现内容：

- Core Stage 01–46 的已有 stage 文件保持与 Advanced V1 基线一致。
- `core/` 保持一致。
- `advanced/` A–F 保持一致。
- 本次比较覆盖 199 个文件，SHA-256 mismatch = 0。

根 `CMakeLists.txt` 是集成入口，允许新增 `MINICPU_BUILD_IMPLEMENTATION` option 和新的检查项；它不属于上述冻结内容哈希集合。
