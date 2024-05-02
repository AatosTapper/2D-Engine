#include "Renderer.h"

#include "Sprite.h"
#include "Shader.h"
#include "../../config.h"

#include <cassert>

static Shader *selected_shader = nullptr;

void Renderer::init()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);
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

void Renderer::draw_sprite(const Sprite &sprite)
{
    assert(selected_shader && "Cannot draw a sprite without a shader being selected");

    glm::mat4 view_mat(1.0f);
    view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -10.0f));

    //glm::vec2 camera_dimensions = engine_window.get_dimensions();
    //glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), camera_dimensions.x / camera_dimensions.y, 0.1f, 100.0f);
    glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    selected_shader->use();
    glActiveTexture(GL_TEXTURE0);
    sprite.texture->bind();
    selected_shader->set_mat4f("u_proj", proj_mat);
    selected_shader->set_mat4f("u_view", view_mat);
    selected_shader->set_mat4f("u_transform", sprite.get_transform_matrix());

    sprite.vao->bind();
    sprite.ebo->bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sprite.ebo->get_elements()), GL_UNSIGNED_INT, 0);
    sprite.vao->unbind();
    sprite.ebo->unbind();
}