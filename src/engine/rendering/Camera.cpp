#include "Camera.h"

#define WORLD_UP glm::vec3(0.0f, 1.0f, 0.0f)

Camera::Camera(const float aspect_ratio, const float field_of_view) : 
    fov(field_of_view),
    m_position(glm::vec3(0.0f)), 
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    m_delta_pos(glm::vec3(0.0f)),
    pitch(0.0f), yaw(-90.0f),
    m_vp_mat(std::make_unique<glm::mat4>(1.0f))
{
    update(aspect_ratio);
}

void Camera::update(const float aspect_ratio)
{
    m_position += m_delta_pos;
    m_delta_pos = glm::vec3(0.0f);
    m_update_direction();
    m_front = m_direction;
    m_up = glm::normalize(glm::cross(m_direction, glm::normalize(glm::cross(WORLD_UP, m_direction))));
    m_right = glm::normalize(glm::cross(m_front, m_up));
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 1000.0f);
    *m_vp_mat = projection * m_view;
}

void Camera::forward(const float amount)
{
    m_delta_pos += amount * m_front;
}

void Camera::back(const float amount)
{
    m_delta_pos -= amount * m_front;
}

void Camera::left(const float amount)
{
    m_delta_pos -= amount * m_right;
}

void Camera::right(const float amount)
{
    m_delta_pos += amount * m_right;
}

void Camera::up(const float amount)
{
    m_delta_pos += amount * WORLD_UP;
}

void Camera::down(const float amount)
{
    m_delta_pos -= amount * WORLD_UP;
}

void Camera::m_update_direction()
{
    m_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_direction.y = sin(glm::radians(pitch));
    m_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_direction = glm::normalize(m_direction);
}