#include "Renderer.h"

#include "Engine.h"

#include "Window.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"
#include "settings.h"

#include <cassert>
#include <stdexcept>

Renderer::Renderer()
  : m_sprite_shader(Shader("../res/shaders/sprite.vert", "../res/shaders/sprite.frag")), 
    m_post_process_shader(Shader("../res/shaders/post_process.vert", "../res/shaders/post_process.frag")),
    m_selected_shader(nullptr)
{

}

Renderer::~Renderer()
{
    delete_framebuffers();
}

void Renderer::init()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_MULTISAMPLE);

    create_framebuffers();
}

void Renderer::start_frame()
{
    if (Engine::instance().get_window()->did_resize())
    {
        regenerate_framebuffer();
        Engine::instance().get_window()->reset_resize_flag();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::clear_queues()
{
    m_selected_shader = nullptr;
    m_sprite_queue.clear();
}

void Renderer::set_shader(Ptr<Shader> shader)
{
    assert(shader && "Cannot select a null shader");
    m_selected_shader = shader;
}

void Renderer::set_view_proj_matrix(const glm::mat4 &vp_mat)
{
    m_selected_vpm = vp_mat;
}

void Renderer::queue_sprite(std::tuple<Ref<const QuadMeshComponent>, glm::mat4> sprite)
{
    m_sprite_queue.push_back(sprite);    
}

void Renderer::draw_frame()
{
    draw_sprites();

    render_framebuffer();
}

void Renderer::draw_sprites()
{
    if (m_selected_shader == nullptr)
    {
        m_selected_shader = &m_sprite_shader;
    }

    for (auto sprite_pair : m_sprite_queue)
    {
        auto sprite = std::get<0>(sprite_pair);
        auto transform = std::get<1>(sprite_pair);

        m_selected_shader->use();

        glActiveTexture(GL_TEXTURE0);
        sprite.get().get_texture()->bind();

        m_selected_shader->set_mat4f("u_view_proj", m_selected_vpm);
        m_selected_shader->set_mat4f("u_transform", transform);

        sprite.get().get_vao()->bind();
        sprite.get().get_ebo()->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sprite.get().get_ebo()->get_elements()), GL_UNSIGNED_INT, 0);
        sprite.get().get_vao()->unbind();
        sprite.get().get_ebo()->unbind();
    }
}

void Renderer::render_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_post_process_shader.use();
    m_screen_quad.get_vao()->bind();
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
    glUniform1i(glGetUniformLocation(m_post_process_shader.get_id(), "tex_col"), 0);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, m_texture_depth_buffer);
    glUniform1i(glGetUniformLocation(m_post_process_shader.get_id(), "tex_dep"), 1);

    m_screen_quad.get_vao()->bind();
    m_screen_quad.get_ebo()->bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_screen_quad.get_ebo()->get_elements()), GL_UNSIGNED_INT, 0);
    m_screen_quad.get_vao()->unbind();
    m_screen_quad.get_ebo()->unbind();
}

void Renderer::create_framebuffers()
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    // color buffer

    auto tex_format = Settings::HDR ? GL_RGBA16F : GL_RGBA;

    glGenTextures(1, &m_texture_color_buffer);
    glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, tex_format, 
        Engine::instance().get_window()->get_width(), Engine::instance().get_window()->get_height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_color_buffer, 0);

    // depth buffer

    glGenTextures(1, &m_texture_depth_buffer);
    glBindTexture(GL_TEXTURE_2D, m_texture_depth_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
        Engine::instance().get_window()->get_width(), Engine::instance().get_window()->get_height(), 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture_depth_buffer, 0);
    
    // stencil renderbuffer

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, 
        Engine::instance().get_window()->get_width(), Engine::instance().get_window()->get_height());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::delete_framebuffers()
{
    glDeleteRenderbuffers(1, &m_rbo);
    glDeleteTextures(1, &m_texture_depth_buffer);
    glDeleteTextures(1, &m_texture_color_buffer);
    glDeleteFramebuffers(1, &m_framebuffer);
}

void Renderer::regenerate_framebuffer()
{
    delete_framebuffers();
    create_framebuffers();
}