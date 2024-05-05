#pragma once

#include <memory>

#include "Scene.h"
#include "Window.h"
#include "rendering/Camera.h"


// Use like this:

// Engine::set_window(...);
// Engine::run();

namespace Engine
{
    void init(int _fps_cap);

    void set_window(Window *_window);
    void set_camera(Camera *_camera);
    void set_scene(Scene *_scene);

    void run();

    Window *get_window();
    Camera *get_camera();
    Scene *get_scene();
};