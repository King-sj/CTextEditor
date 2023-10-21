cmake_minimum_required(VERSION 3.20)
# add_compile_options(--gtest_color=yes --ctest_color=yes) # no this
# include_directories(../3rdparty/gtest/googletest/include/)
# link_libraries(${GTEST_LIB})
set(all_include_list)
set(all_lib_list)
list(APPEND all_include_list ../include/)
list(APPEND all_include_list ../3rdparty/gtest/googletest/include/)
list(APPEND all_lib_list ${GTEST_LIB})
list(APPEND all_lib_list SString)
MESSAGE("Test use all lib ${all_lib_list} ${SString}")
macro(AddTest target_name surfix) #input cpp/c filename
    add_executable(${target_name} ${target_name}.${surfix})
    target_include_directories(${target_name} PRIVATE ${all_include_list})
    target_link_libraries(${target_name} ${all_lib_list})
    add_test(NAME ${target_name}
            COMMAND $<TARGET_FILE:${target_name}>
    )
endmacro(AddTest)

#find all file
aux_source_directory(./ test_src)
MESSAGE("test_src ${test_src}")

file(GLOB all_files ./*.cpp)
MESSAGE("all test file in tests ${all_files}")
foreach(full_name ${all_files})
    get_filename_component(name ${full_name} NAME_WE)
    AddTest(${name} cpp)
endforeach()