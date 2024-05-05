#include "SpriteComponent.h"

#include <iostream>

#include "../rendering/VertexBufferLayout.h"
#include "../rendering/VertexArray.h"
#include "../rendering/VertexBuffer.h"
#include "../rendering/IndexBuffer.h"

static bool mesh_created = false;
static std::unique_ptr<VertexArray> vao_memory = nullptr;
static std::unique_ptr<IndexBuffer> ebo_memory = nullptr;
static std::unique_ptr<VertexBuffer> vbo_memory = nullptr;

// each sprite has the exact same vertices and indices
static constexpr float vertices[] = {
     1.0f,  1.0f, 0.0f,     1.0f, 1.0f,
     1.0f, -1.0f, 0.0f,     1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,     0.0f, 1.0f
};

static constexpr uint32_t indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

SpriteComponent::SpriteComponent(float width, float height)
{
    transform.scale_x = width;
    transform.scale_y = height;

    if (!mesh_created)
    {
        mesh_created = true;

        vao_memory = std::make_unique<VertexArray>();
        vbo_memory = std::make_unique<VertexBuffer>();
        ebo_memory = std::make_unique<IndexBuffer>();

        VertexBufferLayout layout;
        layout.push<float>(3); // position
        layout.push<float>(2); // texture coordinates

        vbo_memory->set_data(vertices, sizeof(vertices));
        ebo_memory->set_data(indices, 6);
        vao_memory->add_buffer(*vbo_memory, layout);
    }

    vao = vao_memory.get();
    vbo = vbo_memory.get();
    ebo = ebo_memory.get();
}

void SpriteComponent::add_texture(const std::string &filepath)
{
    texture = std::make_shared<Texture>(filepath);
}

void SpriteComponent::add_texture(std::shared_ptr<Texture> &ptr)
{
    texture = ptr;
}