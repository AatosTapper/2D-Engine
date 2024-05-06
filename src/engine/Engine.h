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
    void init();

    void set_camera(Camera *_camera);
    void set_scene(Scene *_scene);

    void run();

    Window *get_window();
    Camera *get_camera();
    Scene *get_scene();
};