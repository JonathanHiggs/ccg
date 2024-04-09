cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(
    vcpkg-example
    LANGUAGES CXX
)

include(InstallCCG)
find_package(ccg CONFIG REQUIRED)

add_executable(vcpkg-example)

set_target_properties(
    vcpkg-example
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_RQUIRED ON
)

ccg_generate(
    "${CMAKE_SOURCE_DIR}/input.ccg.json"
    "${CMAKE_SOURCE_DIR}/config.ccg.json"
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

target_sources(vcpkg-example PRIVATE ${SOURCE_FILES})

target_compile_options(vcpkg-example PRIVATE "/std:c++20")

target_include_directories(vcpkg-example PRIVATE "${CMAKE_SOURCE_DIR}/src")