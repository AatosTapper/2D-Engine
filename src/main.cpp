#include "config.h"
#include "engine/window.h"
#include "engine/rendering/VertexBuffer.h"
#include "engine/rendering/VertexArray.h"
#include "engine/rendering/IndexBuffer.h"
#include "engine/rendering/VertexBufferLayout.h"
#include "engine/rendering/Shader.h"
#include "engine/rendering/Texture.h"

#include "engine/rendering/sprite.h"

#include <vector>
#include <memory>

// settings
constexpr int SCR_WIDTH = 1280;
constexpr int SCR_HEIGHT = 720;

int main()
{
    Window engine_window(SCR_WIDTH, SCR_HEIGHT);

    // TODO: move these into a renderer class
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");

    std::shared_ptr<Texture> tex = std::make_shared<Texture>("../res/textures/wood-texture.jpg");

    Sprite sp1(1.0f);
    sp1.add_texture(tex);
    sp1.position = { 2.0f, 0.0f, 0.0f };
    std::cout << "Got here\n";

    Sprite sp2(1.0f);
    sp2.add_texture(tex);
    sp2.position = { -4.0f, -1.0f, 0.0f };
    std::cout << "Got here\n";

    Sprite sp3(1.0f);
    sp3.add_texture(tex);
    sp3.position = { 0.0f, 2.0f, 0.0f };
    std::cout << "Got here\n";
    
    std::vector<Sprite*> sprites = { &sp1, &sp2, &sp3 };

    glm::mat4 view_mat(1.0f);
    view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -10.0f));
    
    // render loop
    while (engine_window.is_open())
    {
        // render here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

        glm::vec2 camera_dimensions = engine_window.get_dimensions();
        glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), camera_dimensions.x / camera_dimensions.y, 0.1f, 100.0f);

        for (auto sprite : sprites)
        {
            sprite->rotation_radians += 0.005f;
            shader.use();
            glActiveTexture(GL_TEXTURE0);
            sprite->texture->bind();
            shader.set_mat4f("u_proj", proj_mat);
            shader.set_mat4f("u_view", view_mat);
            shader.set_mat4f("u_transform", sprite->get_transform_matrix());

            sprite->vao.bind();
            sprite->ebo.bind();
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sprite->ebo.get_elements()), GL_UNSIGNED_INT, 0);

            sprite->vao.unbind();
            sprite->ebo.unbind();
        }
        engine_window.end_frame();
    }

    return 0;
}