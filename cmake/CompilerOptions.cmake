## Setup Compile Options
message(TRACE "ccg::CompilerOptions")


if (CCG_COMPILER_CLANG)
    target_compile_options(
        ccg_base_target
        INTERFACE
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
            $<$<BOOL:${CCG_ENABLE_IPO}>:-flto=auto>
    )

    target_link_options(
        ccg_base_target
        INTERFACE
            -static-libgcc
            -static-libstdc++
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
    )

elseif(CCG_COMPILER_CLANGCL)
    target_compile_options(
        ccg_base_target
        INTERFACE
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
            $<$<BOOL:${CCG_ENABLE_IPO}>:-flto=auto>
    )

    target_link_options(
        ccg_base_target
        INTERFACE
            -static-libgcc
            -static-libstdc++
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
    )

elseif(CCG_COMPILER_GCC)
    target_compile_options(
        ccg_base_target
        INTERFACE
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
            $<$<BOOL:${CCG_ENABLE_IPO}>:-flto=auto>
    )

    target_link_options(
        ccg_base_target
        INTERFACE
            -static-libgcc
            -static-libstdc++
            $<$<BOOL:${CCG_ENABLE_ASAN}>:-fsanitize=address>
    )

elseif(CCG_COMPILER_MSVC)
    target_compile_definitions(
        ccg_base_target
        INTERFACE
            _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
            $<$<BOOL:${CCG_ENABLE_ASAN}>:_DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION>
    )

    target_compile_options(
        ccg_base_target
        INTERFACE
            $<$<CONFIG:DEBUG>:/FC>              # display full path in diagnostics
            $<$<CONFIG:DEBUG>:/Oi>              # replace calls with intrinsics
            $<$<CONFIG:DEBUG>:/Zi>              # generate complete debug info
            $<$<CONFIG:DEBUG>:/JMC>             # just my code
            $<$<CONFIG:RELEASE>:/Ot>            # prefer fast optimizations
            $<$<BOOL:${CCG_ENABLE_ASAN}>:/fsanitize=address /Zi /INCREMENTAL:NO>
            $<$<BOOL:${CCG_ENABLE_IPO}>:/GL>   # whole program optimization (IPO)
    )

    target_link_options(
        ccg_base_target
        INTERFACE
            $<IF:$<BOOL:${CCG_ENABLE_ASAN}>,/INCREMENTAL:NO,/INCREMENTAL>
    )

else()
    message(SEND_ERROR "CompilerOptions not supported for ${CMAKE_CXX_COMPILER_ID}")
endif()