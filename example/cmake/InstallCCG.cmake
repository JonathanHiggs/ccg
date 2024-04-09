# Build and install ccg from local repo

get_filename_component(CCG_REPO_DIR "${CMAKE_SOURCE_DIR}/.." REALPATH)

message(STATUS "Configure local ccg in ${CCG_REPO_DIR}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CCG_PRESET "msvc.release")
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*")
    set(CCG_PRESET "gcc.release")
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*")
    set(CCG_PRESET "clang.release")
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} --preset ${CCG_PRESET}
    WORKING_DIRECTORY ${CCG_REPO_DIR}
)

execute_process(
    COMMAND ${CMAKE_COMMAND} --build --preset ${CCG_PRESET}
    WORKING_DIRECTORY ${CCG_REPO_DIR}
)

execute_process(
    COMMAND ${CMAKE_COMMAND} --install "${CCG_REPO_DIR}/out/build/${CCG_PRESET}"
    WORKING_DIRECTORY ${CCG_REPO_DIR}
)

set(ccg_DIR "${CCG_REPO_DIR}/out/install/msvc.release/share/ccg")

message(STATUS "Installed local ccg to ${ccg_DIR}")