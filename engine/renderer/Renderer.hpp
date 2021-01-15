#pragma once

#include "types/Types.hpp"

#include <atomic>
#include <thread>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool check_close();

    void begin_frame();
    void end_frame();

    void push_camera(const Camera &cam);
    void pop_camera();

    void draw_cube(Material *material, glm::mat4 transform);
    void draw_plane(Material *material, glm::mat4 transform);
    void draw_mesh(Mesh *mesh, Material *material, glm::mat4 transform);

    void free_resource(Material *mat);
    void free_resource(Mesh *mesh);
    void free_resources();

private:
    void window_events();

    void load_mesh(Mesh *mesh);
    void load_material(Material *mat);

    void init_window();
    void init_opengl();

    void cleanup_opengl();
    void cleanup_window();

    bool m_close = false;

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_GLContext;
};
