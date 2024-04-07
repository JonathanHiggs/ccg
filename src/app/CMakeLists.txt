## ccg executable wrapper

add_executable(ccg)
add_executable(ccg::ccg ALIAS ccg)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(ccg PRIVATE ${source_files})

target_include_directories(
    ccg
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(
    ccg
    PRIVATE
        ccg_core
        fmt::fmt-header-only
)


# install

install(
    TARGETS ccg
    EXPORT ccg-targets
    CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES}
    RUNTIME DESTINATION tools/ccg
)

# install(
#     FILES ${CCG_VERSION_HEADER}
#     DESTINATION include/ccg
# )

install(
    EXPORT ccg-targets
    NAMESPACE ccg::
    DESTINATION share/ccg
)