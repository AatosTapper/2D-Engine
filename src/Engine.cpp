#include "Engine.h"

#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "SceneManager.h"

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

void Engine::init()
{
    m_window = std::make_unique<Window>(Settings::SCR_WIDTH, Settings::SCR_HEIGHT);
    m_camera = std::make_unique<Camera>(Engine::instance().get_window()->get_aspect_ratio(), Settings::CAM_FOV, Settings::CAM_PROJECTION);
    m_camera->back(Settings::CAM_START_DIST);
}

Ptr<Window> Engine::get_window()
{
    return m_window.get();
}

Ptr<Camera> Engine::get_camera()
{
    return m_camera.get();
}

void Engine::render()
{
    Renderer::instance().start_frame();
    Renderer::instance().set_view_proj_matrix(m_camera->get_vp_matrix());
    Renderer::instance().draw_frame();
    m_window->end_frame();
}

void Engine::update_logic()
{
    Renderer::instance().clear_queues();
    SceneManager::instance().get_current_scene()->update();
    m_camera->update(m_window->get_aspect_ratio());
}

void Engine::run()
{
    assert(m_window && "Cannot run game without a window selected");
    assert(m_camera && "Cannot run game without a camera selected");
    assert(SceneManager::instance().get_current_scene() && "Cannot run game without a scene selected");
    
    Renderer::instance().init();

    uint32_t frame_counter = 0;
    uint32_t update_counter = 0;
    double frametime_accumulator = 0.0;
    double last_update = glfwGetTime();
    double update_time = 1.0 / Settings::UPDATES_PER_SEC;
    double fps_log_accumulator = 0.0;

    while (m_window->is_open())
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
