#pragma once

#include <memory>

#include "engine/Scene.h"
#include "engine/Window.h"
#include "engine/rendering/Camera.h"
#include "Ref.h"


// Use like this:

// Engine::set_window(...);
// Engine::run();

namespace Engine
{
    void init();

    void set_camera(Camera *_camera);
    void set_scene(Scene *_scene);

    void run();

    Ptr<Window> get_window();
    Ptr<Camera> get_camera();
    Ptr<Scene> get_scene();
};