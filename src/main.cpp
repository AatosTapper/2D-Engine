#include "config.h"

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// THIS FILE WILL BE ALMOST EMPTY AFTER I'VE DONE SOME REFACTORING
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// ---------------------------------------------------------------

#include "engine/Window.h"
#include "engine/rendering/Shader.h"
#include "engine/rendering/Texture.h"
#include "engine/rendering/Sprite.h"
#include "engine/rendering/Renderer.h"
#include "engine/rendering/Camera.h"

//useless comment 

#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>

// settings
constexpr int SCR_WIDTH = 1280;
constexpr int SCR_HEIGHT = 720;

constexpr double target_frame_duration = 1.0 / 60.0; // Targeting 60 FPS

int main()
{
    Window engine_window(SCR_WIDTH, SCR_HEIGHT);
    Renderer::init();
    Camera camera(engine_window.get_aspect_ratio(), 45.0f);
    camera.back(10.0f);

    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");

    // creating shared textures to be used by multiple sprites
    std::shared_ptr<Texture> tex = std::make_shared<Texture>("../res/textures/wood-texture.jpg");
    std::shared_ptr<Texture> dirt = std::make_shared<Texture>("../res/textures/dirt.jpg");

    // creating three sprites
    Sprite sp1(1.0f);
    sp1.add_texture(dirt);
    sp1.position = { 2.0f, 0.0f, 0.0f };

    Sprite sp2(1.0f);
    sp2.add_texture(tex);
    sp2.position = { -4.0f, -1.0f, 0.0f };

    Sprite sp3(1.2f, 0.8f);
    sp3.add_texture(tex);
    sp3.position = { 0.0f, 2.0f, 0.0f };
    
    // putting them in a list so it's easier to render
    std::vector<Sprite*> sprites = { &sp1, &sp2, &sp3 };
    
    uint32_t frame_counter = 0;
    double frame_time_accumulator = 0.0;
    
    // render loop
    while (engine_window.is_open())
    {   
        double frame_start_time = glfwGetTime();
        frame_counter++;

        // this is just for the animation, it won't stay
        sp1.position.z = (float)sin(glfwGetTime() * 2) * 5;
        sp2.position.z = (float)cos(glfwGetTime()) * 5;
        sp3.position.z = (float)cos(glfwGetTime() * 0.5) * 2;

        camera.update(engine_window.get_aspect_ratio());
        Renderer::start_frame();

        for (auto sprite : sprites)
        {
            sprite->rotation_radians += 0.005f; // animation too

            Renderer::set_view_proj_matrix(camera.get_vp_matrix());
            Renderer::set_shader(&shader);
            Renderer::draw_sprite(*sprite);
        }

        Renderer::end_frame();
        engine_window.end_frame();

        // Cap the frame rate
        const double frame_duration = glfwGetTime() - frame_start_time;
        if (frame_duration < target_frame_duration)
        {
            const double sleep_time = (target_frame_duration - frame_duration) * 1000.0; // Convert to milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(sleep_time)));
        }

        // printing out the frame time approximately every two seconds
        frame_time_accumulator += frame_duration;
        if (frame_counter == 59u * 2)
        {
            frame_counter = 0u;
            frame_time_accumulator /= 59.0 * 2; // take the average
            std::cout << "Frametime (capped): " 
                << static_cast<uint32_t>(frame_time_accumulator * 1000000.0) / 1000.0f << "ms = " 
                << static_cast<uint32_t>(1 / frame_time_accumulator) << " FPS\n";
        }
    }

    return 0;
}