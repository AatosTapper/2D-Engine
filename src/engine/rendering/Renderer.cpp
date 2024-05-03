#include "Renderer.h"

#include "Sprite.h"
#include "Shader.h"

#include <cassert>

static Shader *selected_shader = nullptr;
static glm::mat4 selected_vpm;

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
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
}

void Renderer::end_frame()
{
    selected_shader = nullptr;
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

// TODO: push sprite to queue and render all latere
void Renderer::draw_sprite(const Sprite &sprite)
{
    assert(selected_shader && "Cannot draw a sprite without a shader being selected");

    selected_shader->use();
    glActiveTexture(GL_TEXTURE0);
    sprite.texture->bind();

    selected_shader->set_mat4f("u_view_proj", selected_vpm);
    selected_shader->set_mat4f("u_transform", sprite.get_transform_matrix());

    sprite.vao->bind();
    sprite.ebo->bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sprite.ebo->get_elements()), GL_UNSIGNED_INT, 0);
    sprite.vao->unbind();
    sprite.ebo->unbind();
}