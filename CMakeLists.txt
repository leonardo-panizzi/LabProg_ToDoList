cmake_minimum_required(VERSION 3.29)
project(ProgToDo)
#google testing stuff begin:
# include(FetchContent)

#FetchContent_Declare(
#       googletest
#       URL https://github.com/google/googletest/archive/refs/heads/main.zip
#)
# avoids mid-build installations
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#google testing stuff end

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgToDo main.cpp iface.cpp iface.h TaskList.cpp TaskList.h Task.h)

# google testing
#enable_testing()

#add_executable(
#       ProgToDoTests
#       test/test_task.cpp
#       test/test_tasklist.cpp
#)

#target_link_libraries(
#        ProgToDoTests
#        gtest_main
#)

#include(GoogleTest)
#gtest_discover_tests(ProgToDoTests)
