#include "Engine.h"

#include "engine/rendering/Renderer.h"
#include "engine/rendering/Shader.h"

#include "settings.h"

#include <cassert>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>

static void log_frametime(double frametime)
{
    std::cout << "Frametime (capped): " 
        << static_cast<uint32_t>(frametime * 1000000.0) / 1000.0f << "ms = " 
        << static_cast<uint32_t>(std::round(1.0 / frametime)) << " FPS\n";
}

namespace Engine
{
    std::unique_ptr<Window> window = nullptr;
    Camera *camera = nullptr;
    Scene *current_scene = nullptr;

    void init()
    {
        window = std::make_unique<Window>(Settings::SCR_WIDTH, Settings::SCR_HEIGHT);
    }

    void set_camera(Camera *_camera)
    {
        assert(_camera);
        camera = _camera;
    }

    void set_scene(Scene *_scene)
    {
        assert(_scene);
        current_scene = _scene;
    }

    Ptr<Window> get_window()
    {
        return window.get();
    }

    Ptr<Camera> get_camera()
    {
        return camera;
    }

    Ptr<Scene> get_scene()
    {
        return current_scene;
    }

    static void render()
    {
        Renderer::instance().start_frame();
        Renderer::instance().set_view_proj_matrix(camera->get_vp_matrix());
        Renderer::instance().draw_frame();
        window->end_frame();
    }

    static void update_logic()
    {
        Renderer::instance().clear_queues();
        current_scene->update();
        camera->update(window->get_aspect_ratio());
    }

    void run()
    {
        assert(window && "Cannot run game without a window selected");
        assert(camera && "Cannot run game without a camera selected");
        assert(current_scene && "Cannot run game without a scene selected");
        
        Renderer::instance().init();

        uint32_t frame_counter = 0;
        uint32_t update_counter = 0;
        double frametime_accumulator = 0.0;
        double last_update = glfwGetTime();
        double update_time = 1.0 / Settings::UPDATES_PER_SEC;
        double fps_log_accumulator = 0.0;

        while (window->is_open())
        {   
            double frame_start_time = glfwGetTime();
            double delta_time = frame_start_time - last_update;
            last_update += delta_time;
            frametime_accumulator += delta_time;
            fps_log_accumulator += delta_time;
            frame_counter++;

            while (frametime_accumulator > update_time)
            {
                update_logic();
                update_counter++;
                frametime_accumulator -= update_time;
            }

            render();
            
            // logging
            if (update_counter == static_cast<uint32_t>(Settings::UPDATES_PER_SEC))
            {
                fps_log_accumulator /= static_cast<double>(frame_counter);
                log_frametime(fps_log_accumulator);
                fps_log_accumulator = 0.0;
                update_counter = 0u;
                frame_counter = 0u;
            }
        }
    }
}
