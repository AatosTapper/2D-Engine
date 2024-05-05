#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "../../config.h"
#include "TransformComponent.h"
#include "../rendering/Texture.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Texture;

class Sprite
{
public:
    Sprite(float width, float height);
    Sprite(float size) : Sprite(size, size) {}
    Sprite() : Sprite(1.0f, 1.0f) {} // inits with default dimensions of 1.0f 
    
    // transforms
    Transform2DComponent transform;

    // rendering variables
    VertexArray *vao;
    IndexBuffer *ebo;
    std::shared_ptr<Texture> texture{};

    void add_texture(const std::string &filepath);
    void add_texture(std::shared_ptr<Texture> &ptr);

private:
    VertexBuffer *vbo;  
};