#include "Engine.h"

#include "rendering/Renderer.h"
#include "rendering/Shader.h"

#include <cassert>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>

Window *Engine::window = nullptr;
Camera *Engine::camera = nullptr;
Scene *Engine::current_scene = nullptr;

Engine::Engine(int _fps_cap) : fps_cap(_fps_cap)
{
    
}

void Engine::set_window(Window *_window)
{
    assert(_window);
    window = _window;
}

void Engine::set_camera(Camera *_camera)
{
    assert(_camera);
    camera = _camera;
}

void Engine::set_scene(Scene *_scene)
{
    assert(_scene);
    current_scene = _scene;
}

// This function is still fucking shit but at least it's hidden...
void Engine::run()
{
    assert(window && "Cannot run game without a window selected");
    assert(camera && "Cannot run game without a camera selected");
    assert(current_scene && "Cannot run game without a scene selected");
    
    Renderer::init();

    Shader shader("../res/shaders/default.vert", "../res/shaders/default.frag");

    uint32_t frame_counter = 0;
    double frame_time_accumulator = 0.0;
    const double target_frame_duration = 1.0 / fps_cap;

    while (window->is_open())
    {   
        double frame_start_time = glfwGetTime();
        frame_counter++;

        // game logic
        current_scene->update();
        camera->update(window->get_aspect_ratio());

        Renderer::start_frame();
        Renderer::set_view_proj_matrix(camera->get_vp_matrix());
        Renderer::set_shader(&shader);
        Renderer::draw_sprites();
        Renderer::end_frame();

        window->end_frame();

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
}