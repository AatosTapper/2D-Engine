#include "config.h"

//
//
//
//
// THIS FILE IS A FUCKING MESS RN
//
//
//
//

#include "engine/Window.h"
#include "engine/rendering/Shader.h"
#include "engine/rendering/Texture.h"
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
    Window engine_window(SCR_WIDTH, SCR_HEIGHT);
    Renderer::init();
    Camera camera(engine_window.get_aspect_ratio(), 45.0f, PROJ_3D);
    camera.back(10.0f);

    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");

    // creating shared textures to be used by multiple sprites
    std::shared_ptr<Texture> tex = std::make_shared<Texture>("../res/textures/wood-texture.jpg");
    std::shared_ptr<Texture> dirt = std::make_shared<Texture>("../res/textures/dirt.jpg");

    Scene main_scene;

    std::unique_ptr<ImageGameObject> kuutio = std::make_unique<ImageGameObject>();
    kuutio->sprite.dimension = { 1.5f, 1.5f };
    kuutio->sprite.add_texture(tex);

    GameObject::id_t kuutio_id = kuutio->get_id();

    std::unique_ptr<GameObject> scene_object = std::move(kuutio);
    main_scene.add_game_object(scene_object);

    uint32_t frame_counter = 0;
    double frame_time_accumulator = 0.0;
    
    // render loop
    while (engine_window.is_open())
    {   
        double frame_start_time = glfwGetTime();
        frame_counter++;

        auto kuutio_from_scene = main_scene.get_game_object(kuutio_id);
        // this is just for the animation, it won't stay
        if (auto* image_game_object_ptr = dynamic_cast<ImageGameObject*>(kuutio_from_scene.value())) 
        {
            image_game_object_ptr->sprite.rotation_radians += 0.005f;
            image_game_object_ptr->sprite.position.z = (float)sin(glfwGetTime() * 2) * 5;
            image_game_object_ptr->sprite.position.x = (float)sin(glfwGetTime() * (-0.5f)) * 2;
        }

        camera.update(engine_window.get_aspect_ratio());
        Renderer::start_frame();

        Renderer::set_view_proj_matrix(camera.get_vp_matrix());
        Renderer::set_shader(&shader);
        if (auto* image_game_object_ptr = dynamic_cast<ImageGameObject*>(kuutio_from_scene.value())) 
        {
            Renderer::draw_sprite(image_game_object_ptr->sprite);
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