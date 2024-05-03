#pragma once

#include "../../config.h"

class Transform2DComponent
{
public:
    glm::vec2 position{0.0f};

    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};

class Transform3DComponent
{
public:
    glm::vec3 position{0.0f};

    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};