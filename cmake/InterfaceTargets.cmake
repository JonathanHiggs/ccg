## Setup Interface Targets
message(TRACE "ccg::InterfaceTargets")


add_library(ccg_base_target INTERFACE)
add_library(ccg::ccg_base_target ALIAS ccg_base_target)

target_compile_features(ccg_base_target INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

target_link_libraries(
    ccg_base_target
    INTERFACE
        fmt::fmt-header-only
        pantor::inja
        nlohmann_json::nlohmann_json
        spdlog::spdlog_header_only
)


if (CCG_BUILD_TESTS)
    add_library(ccg_test_base_target INTERFACE)
    add_library(ccg::ccg_test_base_target ALIAS ccg_test_base_target)

    target_link_libraries(ccg_test_base_target INTERFACE ccg_base_target)
endif()


include(CompilerDefinitions)
include(CompilerOptions)
include(CompilerWarnings)