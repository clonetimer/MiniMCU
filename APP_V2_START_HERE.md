# MiniMCU App V2 — Start Here

App V1 已冻结；V2 是独立后续版本，目录为：

```text
applications/minimcu_app_v1/   # frozen runtime/app baseline
applications/minimcu_app_v2/   # debugger-focused follow-up
```

V2 只升级 Explore：

- RV32I/Zicsr 反汇编
- side-effect-free ROM/RAM memory peek
- PC breakpoint
- breakpoint-aware Continue

Learn / Lab 的课程边界不扩大。

先读：

1. `applications/minimcu_app_v2/docs/DESIGN_PLAN.md`
2. `applications/minimcu_app_v2/docs/ARCHITECTURE.md`
3. `applications/minimcu_app_v2/docs/API_CONTRACT.md`

构建：

```bash
cmake -S applications/minimcu_app_v2 -B build-app-v2 -DCMAKE_BUILD_TYPE=Release
cmake --build build-app-v2 --parallel
ctest --test-dir build-app-v2 --output-on-failure
./build-app-v2/minimcu_app_v2
```

默认：`http://127.0.0.1:8788`
