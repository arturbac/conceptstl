function(add_ut_test source_file_name)

  get_filename_component(test_executable_name ${source_file_name} NAME_WE)
  add_executable(${test_executable_name} ${source_file_name})
  target_link_libraries(${test_executable_name} PRIVATE conceptstl::header_only )
  
  target_link_libraries(${test_executable_name} PRIVATE boost::ut )
  
  target_compile_definitions(${test_executable_name} PRIVATE SIMPLE_ENUM_OPT_IN_STATIC_ASSERTS BOOST_UT_DISABLE_MODULE)
  add_test(NAME "${test_executable_name}"
           COMMAND ${test_executable_name})

  target_compile_options(${test_executable_name} PRIVATE ${STRICT_CXX_FLAGS})
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    target_compile_options(${test_executable_name} PRIVATE ${clang_default_warnings} )
    target_compile_options(${test_executable_name} PRIVATE -Wno-global-constructors -Wno-exit-time-destructors -Wno-missing-variable-declarations)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options( ${test_executable_name} PRIVATE -Wall -Wextra )
  endif()

endfunction()
