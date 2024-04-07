## Default cmake settings
message(TRACE "ccg::StandardSettings")


# Set default build type to 'Release' when not specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type specified, default set to 'Release'")

    set(CMAKE_BUILD_TYPE "Release"
        CACHE STRING "Choose the type of build, options are: Debug RelWithDebInfo Release MinSizeRel"
        FORCE
    )

    # Set build type options for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "RelWithDebInfo" "Release" "MinSizeRel")
endif()