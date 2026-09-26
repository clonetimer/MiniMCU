# Main teaching path. Keep the six learning phases visible in both the
# directory tree and the CMake hierarchy.
add_subdirectory(01_foundations)
add_subdirectory(02_cpu_rv32i)
add_subdirectory(03_system_software)
add_subdirectory(04_peripherals)
add_subdirectory(05_integration)
add_subdirectory(06_modeling)

# Optional communication-protocol track. Core chapters 01-46 remain the default.
if(MINICPU_BUILD_PROTOCOL_TRACK)
 add_subdirectory(07_protocols)
endif()
