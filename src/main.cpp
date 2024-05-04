#include "config.h"

#include "engine/Window.h"
#include "engine/rendering/Shader.h"
#include "engine/rendering/Sprite.h"
#include "engine/rendering/Renderer.h"
#include "engine/rendering/Camera.h"

#include "engine/Scene.h"
#include "engine/gameobjects/ImageGameObject.h"

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
    // initing the engine and graphics stuff
    Window engine_window(SCR_WIDTH, SCR_HEIGHT);
    Renderer::init();

    // creating a camera
    Camera camera(engine_window.get_aspect_ratio(), 45.0f, PROJ_3D);
    camera.back(10.0f);
    
    // creating a shader (obviously)
    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");

    // creating a scene
    Scene main_scene;
    
    // creating a game object of type ImageGameObject and putting it into the scene
    main_scene.add_game_object(CREATE_GAME_OBJECT(ImageGameObject));

    uint32_t frame_counter = 0;
    double frame_time_accumulator = 0.0;
    
    // render loop
    while (engine_window.is_open())
    {   
        double frame_start_time = glfwGetTime();
        frame_counter++;

        // game logic
        main_scene.update();
        camera.update(engine_window.get_aspect_ratio());

        Renderer::start_frame();
        Renderer::set_view_proj_matrix(camera.get_vp_matrix());
        Renderer::set_shader(&shader);
        Renderer::draw_sprites();
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