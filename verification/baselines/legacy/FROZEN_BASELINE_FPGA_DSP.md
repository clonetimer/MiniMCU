# Frozen Baseline · FPGA + DSP Extension V1

基线为 `MiniMCU_Implementation_source_v1`。

逐文件 SHA-256 对比时，排除两个“有意扩展入口”：
- 根 `CMakeLists.txt`：增加 `MINICPU_BUILD_FPGA_DSP`、DSP 子目录和 FPGA/DSP source-map/smoke tests。
- `implementation/README.md`：只追加 Level 4 课程索引。

其余基线文件：**414 checked, 0 mismatch, 0 missing**。

新增内容位于 `fpga/`、`dsp/`、`implementation/fpga_series/`、`implementation/dsp_series/` 以及本扩展的说明/manifest 文件中。
