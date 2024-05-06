#include "Renderer.h"

#include "../components/SpriteComponent.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <cassert>

void Renderer::init()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_FRAMEBUFFER_SRGB);
}

void Renderer::start_frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::end_frame()
{
    selected_shader = nullptr;
    sprite_queue.clear();
}

void Renderer::set_shader(Shader *shader)
{
    assert(shader && "Cannot select a null shader");
    selected_shader = shader;
}

void Renderer::set_view_proj_matrix(const glm::mat4 &vp_mat)
{
    selected_vpm = vp_mat;
}

void Renderer::queue_sprite(std::tuple<const SpriteComponent*, glm::mat4> sprite)
{
    assert(std::get<0>(sprite) && "Cannot queue an empty sprite");
    sprite_queue.push_back(sprite);    
}

void Renderer::draw_sprites()
{
    if (selected_shader == nullptr)
    {
        selected_shader = &sprite_shader;
    }

    for (auto sprite_pair : sprite_queue)
    {
        auto sprite = std::get<0>(sprite_pair);
        auto transform = std::get<1>(sprite_pair);

        selected_shader->use();

        glActiveTexture(GL_TEXTURE0);
        sprite->texture->bind();

        selected_shader->set_mat4f("u_view_proj", selected_vpm);
        selected_shader->set_mat4f("u_transform", transform);

        sprite->get_vao()->bind();
        sprite->get_ebo()->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sprite->get_ebo()->get_elements()), GL_UNSIGNED_INT, 0);
        sprite->get_vao()->unbind();
        sprite->get_ebo()->unbind();
    }
}