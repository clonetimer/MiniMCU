# MiniMCU Advanced Verification Results

## Advanced Release build

- Advanced lessons registered: 18
- Executed: 18
- Passed: 18
- Failed: 0

## Full project regression

- Registered CTest tests: 66
- Executed and passed: 65
- Skipped: 1 (`rtl_simulation`, using the existing project skip mechanism when the external RTL simulator is unavailable)
- Failed: 0

The exact CTest transcript is in `full_ctest.log`.

## Sanitizers

All 18 Advanced tests also pass in a Debug build with AddressSanitizer + UndefinedBehaviorSanitizer enabled. See `sanitizer_ctest.log`.

## Frozen Core check

- Original files compared: 269
- SHA-256 mismatches: 0
- The root `CMakeLists.txt` is intentionally excluded from this equality check because it contains the new `MINICPU_BUILD_ADVANCED` integration switch and `add_subdirectory(advanced)` hook.

Per-lesson runtime stdout is stored as `A01_...log` through `F03_...log`.
