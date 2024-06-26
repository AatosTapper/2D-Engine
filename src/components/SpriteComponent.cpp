#include "SpriteComponent.h"

#include <iostream>
#include <cassert>

#include "rendering/VertexBufferLayout.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"

// this is probably an anti-pattern but it should work fine
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

QuadMeshComponent::QuadMeshComponent(float width, float height)
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

    m_vao = vao_memory.get();
    m_vbo = vbo_memory.get();
    m_ebo = ebo_memory.get();
}

void SpriteComponent::add_texture(const std::string &filepath)
{
    m_texture = std::make_shared<Texture>(filepath);
}

void SpriteComponent::add_texture(std::shared_ptr<Texture> &ptr)
{
    m_texture = ptr;
}

std::shared_ptr<Texture> SpriteComponent::get_texture() const
{
    assert(m_texture && "Cannot get a texture that isn't initialized yet");
    return m_texture;
}