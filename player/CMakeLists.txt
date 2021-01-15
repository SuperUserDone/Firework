cmake_minimum_required(VERSION 3.0.0)

add_executable(firework-player main.cpp)

target_link_libraries(firework-player firework-engine)