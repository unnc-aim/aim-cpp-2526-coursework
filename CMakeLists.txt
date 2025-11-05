cmake_minimum_required(VERSION 3.10)
project(cpp_exam)

set(CMAKE_CXX_STANDARD 14)

# 启用测试
enable_testing()

# 添加测试用例
set(TEST_CASES 1 2 3 4 5 6 7 8)
foreach(TEST_NUM ${TEST_CASES})
    add_test(
        NAME test_${TEST_NUM}
        COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_SOURCE_DIR}/testcases/expected_${TEST_NUM}.txt
            ${CMAKE_CURRENT_BINARY_DIR}/output_${TEST_NUM}.txt
    )
    
    # 在测试前运行程序生成输出
    add_test(
        NAME run_test_${TEST_NUM}
        COMMAND sh -c "$<TARGET_FILE:cpp_exam> < ${CMAKE_CURRENT_SOURCE_DIR}/testcases/input_${TEST_NUM}.txt > ${CMAKE_CURRENT_BINARY_DIR}/output_${TEST_NUM}.txt 2>&1"
    )
    
    # 设置测试依赖
    set_tests_properties(test_${TEST_NUM} PROPERTIES DEPENDS run_test_${TEST_NUM})
endforeach()

# 设置测试属性
foreach(TEST_NUM ${TEST_CASES})
    set_tests_properties(run_test_${TEST_NUM} PROPERTIES TIMEOUT 10)
    set_tests_properties(test_${TEST_NUM} PROPERTIES TIMEOUT 5)
endforeach()
