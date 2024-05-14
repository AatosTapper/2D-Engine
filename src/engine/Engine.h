#pragma once

#include <memory>

#include "engine/Scene.h"
#include "engine/Window.h"
#include "engine/rendering/Camera.h"
#include "Ref.h"
#include "singleton.h"

// Use like this:

// Engine::set_window(...);
// Engine::run();

class Engine
{
public:
    void init();

    IMPL_SINGLETON_DISPATCHER(Engine)

    void set_camera(Camera *_camera);

    void run();

    Ptr<Window> get_window();
    Ptr<Camera> get_camera();

private:
    std::unique_ptr<Window> window = nullptr;
    Camera *camera = nullptr;

    void render();
    void update_logic();
};