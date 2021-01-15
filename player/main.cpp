#include <iostream>

#include <Firework.hpp>

int main(int argc, char const *argv[])
{
    Renderer render;

    Mesh mesh({{{0.5f, 0.5f, 0.0f}},
               {{0.5f, -0.5f, 0.0f}},
               {{-0.5f, -0.5f, 0.0f}},
               {{-0.5f, 0.5f, 0.0f}}},
              {0, 1, 3, 1, 2, 3});
    Material mat;



    while (!render.check_close())
    {
        render.begin_frame();

        render.draw_mesh(&mesh, &mat, glm::mat4(1.0f));

        render.end_frame();
    }

    return 0;
}
