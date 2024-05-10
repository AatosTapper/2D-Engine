#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "config.h"
#include "engine/components/TransformComponent.h"
#include "engine/rendering/Texture.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;

class SpriteComponent
{
public:
    SpriteComponent(float width, float height);
    SpriteComponent(float size) : SpriteComponent(size, size) {}
    SpriteComponent() : SpriteComponent(1.0f, 1.0f) {} // inits with default dimensions of 1.0f 
    
    Transform2DComponent transform;
    
    void add_texture(const std::string &filepath);
    void add_texture(std::shared_ptr<Texture> &ptr);
    std::shared_ptr<Texture> get_texture() const; // also checks if the texture exists yet

    [[nodiscard]] VertexArray *get_vao() const { return vao; }
    [[nodiscard]] IndexBuffer *get_ebo() const { return ebo; }

private:
    VertexArray *vao;
    IndexBuffer *ebo;
    VertexBuffer *vbo;
    std::shared_ptr<Texture> texture = nullptr;
};