#include "sprite.h"

#include "VertexBufferLayout.h"

#include <iostream>

VertexArray Sprite::vao;
IndexBuffer Sprite::ebo;
VertexBuffer Sprite::vbo;
bool Sprite::mesh_initialized = false;

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

Sprite::Sprite(float width, float height) : dimension({ width, height })
{
    if (!mesh_initialized)
    {
        mesh_initialized = true;

        VertexBufferLayout layout;
        layout.push<float>(3); // position
        layout.push<float>(2); // texture coordinates

        vbo.set_data(vertices, sizeof(vertices));
        ebo.set_data(indices, 6);
        vao.add_buffer(vbo, layout);

        std::cout << "Created the mesh for sprites\n";
    }
}

void Sprite::add_texture(const std::string &filepath)
{
    texture = std::make_shared<Texture>(filepath, false);
}

void Sprite::add_texture(std::shared_ptr<Texture> &ptr)
{
    texture = ptr;
}

glm::mat4 Sprite::get_transform_matrix() const
{
    glm::mat4 output(1.0f);
    output = glm::translate(output, position);
    output = glm::rotate(output, rotation_radians, glm::vec3(0.0f, 0.0f, -1.0f));
    output = glm::scale(output, glm::vec3(dimension, 1.0f)); 
    return output;
}