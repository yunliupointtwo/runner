cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14) # for c++14

project(DVL)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

message("CMAKE_SOURCE_DIR:        " ${CMAKE_SOURCE_DIR})
message("PROJECT_SOURCE_DIR:      " ${PROJECT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:        " ${CMAKE_BINARY_DIR})
message("EXECUTABLE_OUTPUT_PATH:  " ${EXECUTABLE_OUTPUT_PATH})
message("LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH})


add_definitions(-Wall -O2)

#-------------------------------------------------------------------------------
# Google Test
#-------------------------------------------------------------------------------

# download and unpack gtest at config time
configure_file(gtest.txt gtest/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gtest
)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gtest
) 
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# add googletest directly to our build. 
# This defines targets gtest and gtest_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)


##-------------------------------------------------------------------------------
## ADB
##-------------------------------------------------------------------------------
#file(
#  GLOB ADB_FILES
#  ${PROJECT_SOURCE_DIR}/adb/*.cpp
#)
#add_library(
#  adb
#  ${ADB_FILES}
#)
#
##-------------------------------------------------------------------------------
## Tests
##-------------------------------------------------------------------------------
#file(
#  GLOB ADB_TESTFILES
#  ${PROJECT_SOURCE_DIR}/adb/t.*.cpp
#)
#add_executable(
#  tests
#  ${ADB_TESTFILES}
#)
#target_link_libraries(
#  tests
#  adb
#  gtest
#  gtest_main
#  pthread
#)
