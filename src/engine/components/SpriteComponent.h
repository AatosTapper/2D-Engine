#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <cassert>

#include "config.h"
#include "engine/components/TransformComponent.h"
#include "engine/rendering/Texture.h"
#include "Ref.h"

// Instructions for how to use are below

class VertexArray;
class VertexBuffer;
class IndexBuffer;

class QuadMeshComponent
{
public:
    QuadMeshComponent(float width, float height);
    QuadMeshComponent(float size) : QuadMeshComponent(size, size) {}
    QuadMeshComponent() : QuadMeshComponent(1.0f, 1.0f) {} // inits with default dimensions of 1.0f 
    virtual ~QuadMeshComponent() {}
    
    Transform2DComponent transform;
    
    [[nodiscard]] VertexArray *get_vao() const { return m_vao; }
    [[nodiscard]] IndexBuffer *get_ebo() const { return m_ebo; }

    virtual std::shared_ptr<Texture> get_texture() const { assert(false); return nullptr; };

private:
    VertexArray *m_vao = nullptr;
    IndexBuffer *m_ebo = nullptr;
    VertexBuffer *m_vbo = nullptr;  
};

class SpriteComponent : public QuadMeshComponent
{
public:
    ~SpriteComponent() override {}

    void add_texture(const std::string &filepath);
    void add_texture(std::shared_ptr<Texture> &ptr);
    std::shared_ptr<Texture> get_texture() const override; // also checks if the texture exists yet

private:
    std::shared_ptr<Texture> m_texture = nullptr;
};

/*
How to use?

---------------------------------------------------------------------
Create a sprite:
---------------------------------------------------------------------

SpriteComponent my_sprite;

---------------------------------------------------------------------
You can also init it with scale variables:
---------------------------------------------------------------------

SpriteComponent my_sprite(my_width, my_heighth);

or

SpriteComponent my_sprite(my_size);

---------------------------------------------------------------------
Then add a texture with a filepath or a shared pointer:
---------------------------------------------------------------------

my_sprite.add_texture("../res/textures/texture_name.png");

or

std::shared_ptr<Texture> my_texture = std::make_shared<Texture>("../res/textures/texture_name.png");
my_sprite.add_texture(my_texture);

---------------------------------------------------------------------
You can change the texture filtering or transforms of the sprite now
---------------------------------------------------------------------

my_sprite.get_texture()->filter_nearest();

or

my_sprite.transform.x = 5.0;

etc.

---------------------------------------------------------------------
Then in the update_components() function of a Entity, 
send the sprite and a transform matrix to renderer:
---------------------------------------------------------------------

//                        game object's transform     sprite's transform
glm::mat4 full_transform = transform.get_matrix() * my_sprite.transform.get_matrix();
Renderer::instance().queue_sprite({ &my_sprite, full_transform });

*/