# Student Layout V4 verification

- Release root build with protocol track + labs: 65/65 CTest PASS.
- Strict warning protocol/lab subset: 17/17 PASS with `-Wall -Wextra -Wpedantic -Werror`.
- ASan + UBSan protocol/lab subset: 17/17 PASS.
- Eight labs independently configure/build/test.
- Default root configuration registers 48 tests and no 47–54/lab targets.
- `MINICPU_BUILD_PROTOCOL_LABS=ON` without the protocol track is rejected at CMake configure time.
- Repository hygiene and student-layout checks pass.
