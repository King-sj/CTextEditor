macro(AddTest target_name surfix) #input cpp/c filename
    add_executable(${target_name} ${target_name}.${surfix})
    add_test(NAME ${target_name}
            COMMAND $<TARGET_FILE:${target_name}>
    )
endmacro(AddTest)

#find all file
aux_source_directory(./ test_src)
MESSAGE("test_src ${test_src}")

file(GLOB all_files ./*.c)
MESSAGE("all test file in tests ${all_files}")
foreach(full_name ${all_files})
    get_filename_component(name ${full_name} NAME_WE)
    AddTest(${name} c)
endforeach()
