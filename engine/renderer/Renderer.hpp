#pragma once

#include "types/Types.hpp"

#include <atomic>
#include <stack>
#include <thread>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct CameraProps
{
    std::shared_ptr<Camera> cam;
    glm::mat4 transform;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool check_close();

    void begin_frame();
    void end_frame();

    void push_camera(const std::shared_ptr<Camera> &cam, const glm::mat4 &transform);
    void pop_camera();
    void refresh_camera();

    void draw_cube(Material &material, const glm::mat4 &transform);
    void draw_plane(Material &material, const glm::mat4 &transform);
    void draw_mesh(Mesh &mesh, Material &material, const glm::mat4 &transform);

    void free_resource(Material &mat);
    void free_resource(Mesh &mesh);
    void free_resources();

private:
    void window_events();

    void load_mesh(Mesh &mesh);
    void load_material(Material &mat);

    void init_window();
    void init_opengl();

    void cleanup_opengl();
    void cleanup_window();

    std::stack<CameraProps> m_cameras;

    bool m_close = false;

    uint m_camera_buffer = 0;

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_GLContext;
};
