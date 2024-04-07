# Executes code generation for given input and config files
function(ccg_generate input_data_file config_file)
    get_target_property(CCG_EXE ccg::ccg LOCATION)

    execute_process(
        COMMAND ${CCG_EXE}
        ${input_data_file}
        ${config_file}
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
    )
endfunction()