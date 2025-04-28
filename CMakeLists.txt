cmake_minimum_required(VERSION 3.16)
project(ProgToDo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")       #might wanna comment this out
add_subdirectory(ToDoList)
add_subdirectory(google_test)

add_executable(ProgToDo_main main.cpp)

target_link_libraries(ProgToDo_main PRIVATE ProgToDo_LIB)
