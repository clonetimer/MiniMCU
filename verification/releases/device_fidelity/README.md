# Device Fidelity verification archive

Each `vN/` directory contains the evidence produced for that milestone. New releases use stable lowercase names:

- `ctest.txt` — CTest summary/output;
- `sanitizer.txt` — ASan/UBSan result;
- `rtl_verilator.txt` — dynamic RTL result when Verilator was available;
- `changes.sha256` — hashes of release content files;
- optional focused logs use descriptive lowercase names.

These files are evidence, not source inputs. Build trees, `obj_dir/`, Linux module outputs, temporary firmware conversion files, and tool caches must not be committed here.
