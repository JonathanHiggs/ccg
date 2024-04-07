## CCG project options
message(TRACE "ccg::ProjectOptions")


# Compiler dependent feature support
if (CCG_COMPILER_CLANG)
    set(CCG_SUPPORTS_ASAN       ON)
    set(CCG_SUPPORTS_COVERAGE   OFF)
    set(CCG_SUPPORTS_UBSAN      ON)

elseif (CCG_COMPILER_CLANGCL)
    set(CCG_SUPPORTS_ASAN       OFF)
    set(CCG_SUPPORTS_COVERAGE   OFF)
    set(CCG_SUPPORTS_UBSAN      OFF)

elseif (CCG_COMPILER_GCC)
    set(CCG_SUPPORTS_ASAN       ON)
    set(CCG_SUPPORTS_COVERAGE   OFF)
    set(CCG_SUPPORTS_UBSAN      ON)

elseif (CCG_COMPILER_MSVC)
    set(CCG_SUPPORTS_ASAN       ON)
    set(CCG_SUPPORTS_COVERAGE   OFF)
    set(CCG_SUPPORTS_UBSAN      OFF)

endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT output)
if (result)
    set(CCG_SUPPORTS_IPO ON)
else()
    set(CCG_SUPPORTS_IPO OFF)
endif()

message(TRACE "CCG supported options:")
message(TRACE "  CCG_SUPPORTS_ASAN                      ${CCG_SUPPORTS_ASAN}")
message(TRACE "  CCG_SUPPORTS_COVERAGE                  ${CCG_SUPPORTS_COVERAGE}")
message(TRACE "  CCG_SUPPORTS_UBSAN                     ${CCG_SUPPORTS_UBSAN}")
message(TRACE "  CCG_SUPPORTS_IPO                       ${CCG_SUPPORTS_IPO}")


# Option defaults
set(CCG_BUILD_TESTS_DEFAULT         OFF)
set(CCG_ENABLE_ASAN_DEFAULT         OFF)
set(CCG_ENABLE_COVERAGE_DEFAULT     OFF)
set(CCG_ENABLE_UBSAN_DEFAULT        OFF)
set(CCG_ENABLE_IPO_DEFAULT          ${CCG_SUPPORTS_IPO})

if (CCG_BUILD_DEBUG)
    set(CCG_ENABLE_ASSERTS_DEFAULT  ON)
else()
    set(CCG_ENABLE_ASSERTS_DEFAULT  OFF)
endif()

if (PROJECT_IS_TOP_LEVEL)
    set(CCG_ENABLE_WARNINGS_AS_ERRORS   ON)
else()
    set(CCG_ENABLE_WARNINGS_AS_ERRORS   OFF)
endif()

message(TRACE "CCG option defaults:")
message(TRACE "  CCG_BUILD_TESTS_DEFAULT                ${CCG_BUILD_TESTS_DEFAULT}")
message(TRACE "  CCG_ENABLE_ASAN_DEFAULT                ${CCG_ENABLE_ASAN_DEFAULT}")
message(TRACE "  CCG_ENABLE_ASSERTS_DEFAULT             ${CCG_ENABLE_ASSERTS_DEFAULT}")
message(TRACE "  CCG_ENABLE_COVERAGE_DEFAULT            ${CCG_ENABLE_COVERAGE_DEFAULT}")
message(TRACE "  CCG_ENABLE_IPO_DEFAULT                 ${CCG_ENABLE_IPO_DEFAULT}")
message(TRACE "  CCG_ENABLE_UBSAN_DEFAULT               ${CCG_ENABLE_UBSAN_DEFAULT}")
message(TRACE "  CCG_ENABLE_WARNINGS_AS_ERRORS_DEFAULT  ${CCG_ENABLE_WARNINGS_AS_ERRORS_DEFAULT}")


# Read options
option(CCG_BUILD_TESTS                  "Enable building tests"                 ${CCG_BUILD_TESTS_DEFAULT})
option(CCG_ENABLE_ASAN                  "Enable address sanitizer"              ${CCG_ENABLE_ASAN_DEFAULT})
option(CCG_ENABLE_ASSERTS               "Enable debug asserts"                  ${CCG_ENABLE_ASSERTS_DEFAULT})
option(CCG_ENABLE_COVERAGE              "Enable test coverage reporting"        ${CCG_ENABLE_COVERAGE_DEFAULT})
option(CCG_ENABLE_IPO                   "Enable IPO/LTO"                        ${CCG_ENABLE_IPO_DEFAULT})
option(CCG_ENABLE_UBSAN                 "Enable undefined behaviour sanitizer"  ${CCG_ENABLE_UBSAN_DEFAULT})
option(CCG_ENABLE_WARNINGS_AS_ERRORS    "Enable warnings-as-errors"             ${CCG_ENABLE_WARNINGS_AS_ERRORS_DEFAULT})

message(STATUS "CCG option:")
message(STATUS "  CCG_BUILD_TESTS                        ${CCG_BUILD_TESTS}")
message(STATUS "  CCG_ENABLE_ASAN                        ${CCG_ENABLE_ASAN}")
message(STATUS "  CCG_ENABLE_ASSERTS                     ${CCG_ENABLE_ASSERTS}")
message(STATUS "  CCG_ENABLE_COVERAGE                    ${CCG_ENABLE_COVERAGE}")
message(STATUS "  CCG_ENABLE_IPO                         ${CCG_ENABLE_IPO}")
message(STATUS "  CCG_ENABLE_UBSAN                       ${CCG_ENABLE_UBSAN}")
message(STATUS "  CCG_ENABLE_WARNINGS_AS_ERRORS          ${CCG_ENABLE_WARNINGS_AS_ERRORS}")
