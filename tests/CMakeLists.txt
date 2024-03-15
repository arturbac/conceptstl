include(test_functions.cmake)

add_compile_failure_test(vector/should_fail_compile.cc)
add_compile_success_test(vector/should_compile.cc)

add_compile_failure_test(format/should_fail_compile.cc)
add_compile_success_test(format/should_compile.cc)

add_ut_test(concept_stl_ut.cc)
