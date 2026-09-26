# Virtual-chip / RTL extension verification

This report covers the revision that adds `course/06_modeling/46_virtual_chips`, `core/chips.hpp` and the hand-written `rtl/` tree.

## Release C++ / firmware configuration

A clean Release configuration registered 47 CTests. Result:

- 46 executed and passed;
- 0 failed;
- 1 skipped: `rtl_simulation` because no Icarus Verilog or Verilator executable exists in this sandbox.

The dependency-free `rtl_structure` test passed, but it is not an HDL compile.

## Sanitizers

The Debug build with `MINICPU_SANITIZERS=ON`, AddressSanitizer, UndefinedBehaviorSanitizer and leak detection registered the same 47 tests:

- 46 executed and passed;
- 0 failed;
- `rtl_simulation` skipped for the same missing-tool reason;
- no sanitizer diagnostic was emitted.

See `verification/sanitizer/ctest.log`.

## Firmware rebuilt from source

The RV32 firmware was rebuilt with the available Clang RISC-V backend using `rv32i_zicsr_zifencei/ilp32`, then run on the C++ MiniMCU:

```text
bare-metal C: PASS (data/bss/stack/calls/GPIO/UART)
bare-metal timer interrupt: 5 ticks OK
peripheral C: PASS (Flash/IMU/I2C/EEPROM/ADC/DMA)
```

The virtual-chip regression reports:

```text
[PASS] virtual chips: SHT31/BME280/ADS1115/PCA9685/MCP23017/SSD1306/MAX31855/MCP3008/ICM42688 + actuators
```

## RTL verification status

The sandbox was checked for `verilator`, `iverilog`, `vvp`, `yosys`, `slang` and `surelog`; none is installed. Therefore this revision does **not** claim dynamic RTL compile/simulation success in this environment.

The RTL verification assets nevertheless include:

- ALU directed testbench;
- hand-coded SoC smoke firmware testbench;
- compiled bare-metal C firmware testbench;
- compiled Machine Timer interrupt firmware testbench;
- ELF32 RISC-V `PT_LOAD` to `$readmemh` converter;
- retire trace signals intended for future C++/Verilator differential testing.
