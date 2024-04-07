## ccg library tests

add_executable(ccg_core_tests)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(ccg_core_tests PRIVATE ${source_files})

target_include_directories(
    ccg_core_tests
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(
    ccg_core_tests
    PRIVATE
        ccg_test_base_target
        ccg_core
        GTest::gtest
        GTest::gtest_main
)

gtest_discover_tests(ccg_core_tests DISCOVERY_MODE POST_BUILD)
