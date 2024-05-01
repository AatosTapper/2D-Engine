#include "config.h"
#include "engine/window.h"
#include "engine/rendering/VertexBuffer.h"
#include "engine/rendering/VertexArray.h"
#include "engine/rendering/IndexBuffer.h"
#include "engine/rendering/VertexBufferLayout.h"
#include "engine/rendering/Shader.h"

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
    //glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    
    float vertices[] = {
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.5f,  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    VertexBuffer vbo;
    vbo.set_data(vertices, sizeof(vertices));
    IndexBuffer ebo;
    ebo.set_data(indices, 6);

    VertexBufferLayout layout;
    layout.push<float>(3); // pos
    layout.push<float>(3); // col

    VertexArray vao;
    vao.add_buffer(vbo, layout);

    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");
    
    // render loop
    while (engine_window.is_open())
    {
        // render here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor((sin(glfwGetTime()) + 1.0f) * 0.25f, 
                    (cos(glfwGetTime()) + 1.0f) * 0.25f, 
                    (sin(glfwGetTime()) - 1.0f) * (-0.25f), 1.0f);

        shader.use();
        vao.bind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, ebo.get_elements(), GL_UNSIGNED_INT, 0);     

        engine_window.end_frame();
    }

    return 0;
}