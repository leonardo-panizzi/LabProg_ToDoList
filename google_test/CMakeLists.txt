# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
add_executable(Google_Tests_run
        Unit_testing.cpp
        ../ToDoList/TaskList.cpp   # <--- added for unit testing
)
target_link_libraries(Google_Tests_run
        gtest
        gtest_main)