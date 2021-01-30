cmake_minimum_required(VERSION 3.0.0)

find_package(PkgConfig REQUIRED)

pkg_search_module(SDL2 sdl2)

#add_compile_definitions(TRACY_ENABLE)

set(SOURCES 
    renderer/Renderer.cpp
    types/Camera.cpp
    types/Material.cpp
    types/Mesh.cpp

    ../libs/tracy/TracyClient.cpp
    ../libs/glad/src/glad.c
)

include_directories($(SDL2_INCLUDE_DIRS))

add_library(firework-engine ${SOURCES})

target_link_libraries(firework-engine ${SDL2_LIBRARIES} fmt::fmt-header-only dl pthread)