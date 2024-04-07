add_subdirectory(app)
add_subdirectory(cmake)
add_subdirectory(lib)

if (CCG_BUILD_TESTS)
    add_subdirectory(tests)
endif()