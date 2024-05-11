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

class QuadMesh
{
public:
    QuadMesh(float width, float height);
    QuadMesh(float size) : QuadMesh(size, size) {}
    QuadMesh() : QuadMesh(1.0f, 1.0f) {} // inits with default dimensions of 1.0f 
    virtual ~QuadMesh() {}
    
    Transform2DComponent transform;
    
    [[nodiscard]] VertexArray *get_vao() const { return vao; }
    [[nodiscard]] IndexBuffer *get_ebo() const { return ebo; }

protected:
    VertexArray *vao;
    IndexBuffer *ebo;
    VertexBuffer *vbo;  
};

class SpriteComponent : public QuadMesh
{
public:
    ~SpriteComponent() override {}

    void add_texture(const std::string &filepath);
    void add_texture(std::shared_ptr<Texture> &ptr);
    std::shared_ptr<Texture> get_texture() const; // also checks if the texture exists yet

private:
    std::shared_ptr<Texture> texture = nullptr;
};