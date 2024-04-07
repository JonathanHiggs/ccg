## ccg core library

add_library(ccg_core STATIC)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(ccg_core PRIVATE ${source_files})

target_include_directories(
    ccg_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(ccg_core PUBLIC ccg_base_target)