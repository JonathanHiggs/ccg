cmake_minimum_required(VERSION 3.24)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


## Project
file(READ "version.txt" CCG_VERSION)

project(
    ccg
    VERSION ${CCG_VERSION}
    DESCRIPTION "C++20 / CMake Code Generation"
    HOMEPAGE_URL "https://github.com/JonathanHiggs/ccg"
    LANGUAGES CXX
)


## Configure build settings
include(StandardSettings)
include(DetectPlatform)
include(ProjectOptions)
include(Dependencies)
include(InterfaceTargets)

if (CCG_BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
endif()

# include(GitInfo)


## Targets
add_subdirectory(src)
