# Standard project and compiler settings
message(TRACE "ccg::StandardSettings")


# c++ settings
if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)


# Ensure 'compile_commands.json' is generated
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Improve error reporting
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GCC.*")
    add_compile_options(
        $<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics>
        $<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>
    )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/diagnostics:column)
endif()
