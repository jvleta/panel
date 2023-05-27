cmake_minimum_required(VERSION 3.16)

project(panel LANGUAGES CXX VERSION 0.001)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(yanl)
add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(panel-js)
