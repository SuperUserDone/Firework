cmake_minimum_required(VERSION 3.0.0)

project(FIREWORK)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)

include_directories("engine" "libs" "libs/glad/include")

# TODO add platform libs 
set(LINKER_LIBS "dl" "pthread")


add_subdirectory(engine)
add_subdirectory(player)
add_subdirectory(libs)