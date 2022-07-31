

add_definitions("-std=c++20")
add_executable(panel-js main.cpp)
target_link_libraries(panel-js yanl panel)

set_target_properties(panel-js PROPERTIES LINK_FLAGS "-O3 --bind")