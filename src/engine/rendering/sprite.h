#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "../../config.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Sprite
{
public:
    Sprite(float width, float height);
    Sprite(float size) : Sprite(size, size) {}
    Sprite() : Sprite(1.0f, 1.0f) {} // inits with default dimensions of 1.0f 
    
    // transforms
    glm::vec3 position{};
    glm::vec2 dimension{};
    float rotation_radians{};

    // rendering variables
    static VertexArray vao;
    static IndexBuffer ebo;
    std::shared_ptr<Texture> texture{}; 

    void add_texture(const std::string &filepath);
    void add_texture(std::shared_ptr<Texture> &ptr);

    glm::mat4 get_transform_matrix() const;

private:
    static VertexBuffer vbo;
    static bool mesh_initialized;
};