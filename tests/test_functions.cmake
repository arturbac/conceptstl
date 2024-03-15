
macro(setup_compile_check_test)

get_target_property(CONCEPTSTL_INCLUDE_DIRS conceptstl::header_only INTERFACE_INCLUDE_DIRECTORIES)

set(CONCEPTSTL_CXX_FLAGS "")
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

  set(CHECK_COMPILE_SCRIPT "${CMAKE_BINARY_DIR}/check_compilation.sh")

  # Write the script to the file
  file(WRITE ${CHECK_COMPILE_SCRIPT} "${CHECK_COMPILE_SCRIPT_CONTENT}")

  # Set the script's executable permissions
  file(CHMOD ${CHECK_COMPILE_SCRIPT} PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)

endmacro()

setup_compile_check_test()

function(compose_name absolute_path output_variable)
  string(REPLACE "/" "_" path_normalized ${absolute_path})
  set(${output_variable} "${path_normalized}" PARENT_SCOPE)
endfunction()

function(add_compile_success_test source_file)

  set(script_path "${CMAKE_BINARY_DIR}/check_compilation.sh") # Adjust if necessary
  compose_name(${source_file} composed_name )
  add_test(NAME test_${composed_name}_compile_success
           COMMAND ${script_path} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" TRUE)
endfunction()

function(add_compile_failure_test source_file)

  set(script_path "${CMAKE_BINARY_DIR}/check_compilation.sh") # Adjust if necessary
  compose_name(${source_file} composed_name)
  add_test(NAME test_${composed_name}_compile_failure
           COMMAND ${script_path} "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" FALSE)
endfunction()

