#pragma once

#include "../../config.h"
#include "../../util.h"

#include <memory>

#define PROJ_2D true
#define PROJ_3D false

class Camera
{
public:
    Camera(const float aspect_ratio, const float field_of_view, bool ortho);

    float pitch;
    float yaw;
    float fov;

    void update(const float aspect_ratio);
    inline glm::mat4 get_vp_matrix() const { return *m_vp_mat; }
    inline const glm::vec3 &get_position() const { return m_position; }
    inline void set_position(const glm::vec3 &new_pos) { m_position = new_pos; }

    // move
    void forward(const float amount);
    void back(const float amount);
    void left(const float amount);
    void right(const float amount);
    void up(const float amount);
    void down(const float amount);

private:
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_direction; // points in the reverse direction

    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
    glm::vec3 m_delta_pos;
    std::unique_ptr<glm::mat4> m_vp_mat;

    const bool m_ortho;

    void m_update_direction();
};