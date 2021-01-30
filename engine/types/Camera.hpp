#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float fov = 90.f, float near = 0.1, float far = 10000.f);

    void set_fov(float fov);
    void set_near(float near);
    void set_far(float far);

    glm::mat4 get_proj_matrix(float aspect);

    ~Camera();

private:
    float m_fov;
    float m_near;
    float m_far;
};
