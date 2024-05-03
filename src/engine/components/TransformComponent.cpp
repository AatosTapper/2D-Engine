#include "TransformComponent.h"

glm::mat4 Transform2DComponent::get_matrix() const
{
    glm::mat4 output(1.0f);
    output = glm::translate(output, glm::vec3(position, 0.0f));
    //output = glm::rotate(output, rotation_radians, glm::vec2(0.0f, 0.0f));
    //output = glm::scale(output, glm::vec2(dimension)); 
    return output;
}

glm::mat4 Transform3DComponent::get_matrix() const
{
    glm::mat4 output(1.0f);
    output = glm::translate(output, position);
    //output = glm::rotate(output, rotation_radians, glm::vec3(0.0f, 0.0f, -1.0f));
    //output = glm::scale(output, glm::vec3(dimension, 1.0f)); 
    return output;
}
