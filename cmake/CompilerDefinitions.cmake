## Setup Compiler Definitions
message(TRACE "ccg::CompilerDefinitions")


target_compile_definitions(
    ccg_base_target
    INTERFACE
        ${CCG_PLATFORM_DEFINITIONS}
        $<$<BOOL:${CCG_ENABLE_ASSERTS}>:CCG_ENABLE_ASSERTS>
)

if (CCG_BUILD_TESTS)
    target_compile_definitions(
        ccg_test_base_target
        INTERFACE
            CCG_IS_TEST
    )
endif()