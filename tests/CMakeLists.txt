function(newtest test_name test_desc)
    add_executable(${test_name} ${test_name}.test.cpp)
    target_link_libraries(${test_name} aia Catch2::Catch2WithMain)
    add_test(${test_desc} ${test_name})
endfunction()

newtest(builds "Builds")
newtest(stl "Works with stl")