cmake_minimum_required(VERSION 3.29)
project(ProgToDo)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgToDo main.cpp iface.cpp iface.h TaskList.cpp TaskList.h Task.h)
