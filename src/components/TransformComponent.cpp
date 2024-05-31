#include "TransformComponent.h"

glm::mat4 Transform2DComponent::get_matrix() const
{
    glm::mat4 output(1.0f);
    output = glm::translate(output, glm::vec3(static_cast<glm::vec2>(*this), 0.0f));
    output = glm::rotate(output, rotation_rad, glm::vec3(0.0f, 0.0f, -1.0f));
    output = glm::scale(output, glm::vec3(scale_x * scale, scale_y * scale, 1.0f));
    return output;
}

glm::mat4 Transform3DComponent::get_matrix() const
{
    glm::mat4 output(1.0f);
    output = glm::translate(output, static_cast<glm::vec3>(*this));
    output = glm::rotate(output, rotation_rad_x, glm::vec3(-1.0f, 0.0f, 0.0f));
    output = glm::rotate(output, rotation_rad_y, glm::vec3(0.0f, 1.0f, 0.0f));
    output = glm::rotate(output, rotation_rad_z, glm::vec3(0.0f, 0.0f, -1.0f));
    output = glm::scale(output, glm::vec3(scale_x * scale, scale_y * scale, scale_z * scale));
    return output;
}
