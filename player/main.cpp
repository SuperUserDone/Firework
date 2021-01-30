#include <iostream>

#include <Firework.hpp>

#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char const *argv[])
{
    Renderer render;

    Mesh mesh;
    Material mat;

    std::shared_ptr<Camera> cam = std::make_shared<Camera>();

    glm::mat4 view =
        glm::lookAt(glm::vec3(2.f, 2.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    mesh.load_from_file("./data/model.obj");

    while (!render.check_close())
    {
        render.begin_frame();

        render.push_camera(cam, view);

        render.draw_mesh(mesh, mat, glm::mat4(1.f));

        render.end_frame();
    }

    return 0;
}
