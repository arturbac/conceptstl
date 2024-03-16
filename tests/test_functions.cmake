
macro(setup_compile_check_test cxx_stdlib)

get_target_property(CONCEPTSTL_INCLUDE_DIRS conceptstl::header_only INTERFACE_INCLUDE_DIRECTORIES)

set(CONCEPTSTL_CXX_FLAGS "${cxx_stdlib}")
foreach(dir IN LISTS CONCEPTSTL_INCLUDE_DIRS)
  set(CONCEPTSTL_CXX_FLAGS "${CONCEPTSTL_CXX_FLAGS} -I\"${dir}\"")
endforeach()
message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")

set(CHECK_COMPILE_SCRIPT_CONTENT [=[
#!/bin/bash

SOURCE_FILE=$1
EXPECT_SUCCESS=$2
COMPILER="CMAKE_CXX_COMPILER"
CXX_FLAGS="-std=c++23 CONCEPTSTL_CXX_FLAGS"
OUTPUT_EXE="temp_exe"

$COMPILER $CXX_FLAGS -o $OUTPUT_EXE $SOURCE_FILE

if [ $? -eq 0 ]; then
    if [ "$EXPECT_SUCCESS" == "TRUE" ]; then
        echo "Compilation succeeded as expected."
        exit 0
    else
        echo "Compilation succeeded but was expected to fail."
        exit 1
    fi
else
    if [ "$EXPECT_SUCCESS" == "FALSE" ]; then
        echo "Compilation failed as expected."
        exit 0
    else
        echo "Compilation failed but was expected to succeed."
        exit 1
    fi
fi
]=])
  string(REPLACE "CMAKE_CXX_COMPILER" "${CMAKE_CXX_COMPILER}" CHECK_COMPILE_SCRIPT_CONTENT "${CHECK_COMPILE_SCRIPT_CONTENT}")
  string(REPLACE "CONCEPTSTL_CXX_FLAGS" "${CONCEPTSTL_CXX_FLAGS}" CHECK_COMPILE_SCRIPT_CONTENT "${CHECK_COMPILE_SCRIPT_CONTENT}")

  string(FIND ${cxx_stdlib} "=" equal_pos)
  math(EXPR substr_start_pos "${equal_pos} + 1")
  string(SUBSTRING ${cxx_stdlib} ${substr_start_pos} -1 stdlib_right_of_equal)
  # message(STATUS "Substring right of =: ${stdlib_right_of_equal}")
  
  set(CHECK_COMPILE_SCRIPT "${CMAKE_BINARY_DIR}/check_compilation_${stdlib_right_of_equal}.sh")
  # message(STATUS "CHECK_COMPILE_SCRIPT - ${CHECK_COMPILE_SCRIPT}")
  # Write the script to the file
  file(WRITE ${CHECK_COMPILE_SCRIPT} "${CHECK_COMPILE_SCRIPT_CONTENT}")

  # Set the script's executable permissions
  file(CHMOD ${CHECK_COMPILE_SCRIPT} PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)

endmacro()

setup_compile_check_test("-stdlib=libc++")
setup_compile_check_test("-stdlib=libstdc++")

function(compose_name absolute_path output_variable)
  string(REPLACE "/" "_" path_normalized ${absolute_path})
  set(${output_variable} "${path_normalized}" PARENT_SCOPE)
endfunction()

function(add_compile_success_test source_file)
  compose_name(${source_file} composed_name )
  set(script_path_libcxx "${CMAKE_BINARY_DIR}/check_compilation_libc++.sh")
  add_test(NAME test_${composed_name}_libc++_compile_success
           COMMAND ${script_path_libcxx} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" TRUE)
           
  set(script_path_stdcxx "${CMAKE_BINARY_DIR}/check_compilation_libstdc++.sh")
  add_test(NAME test_${composed_name}_stdc++_compile_success
           COMMAND ${script_path_stdcxx} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" TRUE)
  if(ENABLE_TIME_TRACE_BUILD)
    add_executable(test_${composed_name}_time_trace ${CMAKE_CURRENT_SOURCE_DIR}/${source_file} )
    target_link_libraries( test_${composed_name}_time_trace PRIVATE conceptstl::header_only )
  endif()
endfunction()

function(add_compile_failure_test source_file)
  compose_name(${source_file} composed_name)
  set(script_path_libcxx "${CMAKE_BINARY_DIR}/check_compilation_libc++.sh") # Adjust if necessary
  add_test(NAME test_${composed_name}_libc++_compile_failure
           COMMAND ${script_path_libcxx} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" FALSE)
  set(script_path_stdcxx "${CMAKE_BINARY_DIR}/check_compilation_libc++.sh") # Adjust if necessary
  add_test(NAME test_${composed_name}_stdc++_compile_failure
           COMMAND ${script_path_stdcxx} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" FALSE)
endfunction()

