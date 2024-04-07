## Setup project dependencies
message(TRACE "ccg::Dependencies")


find_package(fmt            CONFIG REQUIRED)
find_package(nlohmann_json  CONFIG REQUIRED)
find_package(inja           CONFIG REQUIRED)
find_package(spdlog         CONFIG REQUIRED)


if (CCG_BUILD_TESTS)
    find_package(GTest      CONFIG REQUIRED)
endif()