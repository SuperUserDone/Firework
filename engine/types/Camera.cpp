#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float near, float far) : m_fov(fov), m_near(near), m_far(far) {}

void Camera::set_fov(float fov) { m_fov = fov; }

void Camera::set_near(float near) { m_near = near; }

void Camera::set_far(float far) { m_far = far; }

glm::mat4 Camera::get_proj_matrix(float aspect)
{
    return glm::perspective(m_fov, aspect, m_near, m_far);
}

Camera::~Camera() {}
