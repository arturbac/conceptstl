cmake_minimum_required(VERSION 3.21)
  
project(conceptstl VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(PROJECT_IS_TOP_LEVEL)
  include(cmake/CPM.cmake)

  CPMAddPackage(
    ut
    GITHUB_REPOSITORY boost-ext/ut
    GIT_TAG        master
  )
  find_package(ut REQUIRED)
  
  add_library(Boost_ut_system INTERFACE)
  
  get_target_property(BOOST_UT_INCLUDE_DIR Boost::ut INTERFACE_INCLUDE_DIRECTORIES)
  target_include_directories(Boost_ut_system INTERFACE SYSTEM ${BOOST_UT_INCLUDE_DIR})
  add_library(boost::ut ALIAS Boost_ut_system)
endif()


# Header-only library target
add_library(conceptstl INTERFACE)
add_library(conceptstl::header_only ALIAS conceptstl)

target_include_directories(conceptstl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(PROJECT_IS_TOP_LEVEL)
  include(cmake/building_config.cmake)
  include(cmake/unit_test_integration.cmake)
  enable_testing()
  include(CTest)
  add_subdirectory(tests)
endif()
