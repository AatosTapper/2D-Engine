#pragma once

#include "../../config.h"

// all rotations are in radians

class Transform2DComponent
{
public:
    double x{0.0};
    double y{0.0};
    float scale{1.0f};  // scale applied to all axis
    float scale_x{1.0f};
    float scale_y{1.0f};
    float rotation_rad{0.0f};

    // return the position as a glm vector
    operator glm::vec2() const { return glm::vec2(x, y); }
    operator glm::vec3() const { return glm::vec3(x, y, 0.0); }
    
    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};

class Transform3DComponent
{
public:
    double x{0.0};
    double y{0.0};
    double z{0.0};
    float scale{1.0f};  // scale applied to all axis
    float scale_x{1.0f};
    float scale_y{1.0f};
    float scale_z{1.0f};
    float rotation_rad_x{0.0f};
    float rotation_rad_y{0.0f};
    float rotation_rad_z{0.0f};

    // return the position as a glm vector
    operator glm::vec2() const { return glm::vec2(x, y); }
    operator glm::vec3() const { return glm::vec3(x, y, z); }

    glm::mat4 get_matrix() const;
    operator glm::mat4() const { return get_matrix(); };
};
