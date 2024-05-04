#pragma once

#include "../../config.h"

class Transform2DComponent
{
public:
    double x{0.0};
    double y{0.0};

    operator glm::vec2() const { return glm::vec2(x, y); }

    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};

class Transform3DComponent
{
public:
    double x{0.0};
    double y{0.0};
    double z{0.0};

    operator glm::vec3() const { return glm::vec3(x, y, z); }

    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};