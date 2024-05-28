#pragma once

#include <memory>

#include "engine/Scene.h"
#include "engine/Window.h"
#include "engine/rendering/Camera.h"
#include "Ref.h"
#include "singleton.h"

// Use like this:

// Engine::instance().set_window(...);
// Engine::instance().run();

class Engine
{
public:
    Engine() {}
    void init();

    IMPL_SINGLETON_DISPATCHER(Engine)
    IMPL_NO_COPY(Engine)

    void run();

    Ptr<Window> get_window();
    Ptr<Camera> get_camera();

private:
    std::unique_ptr<Window> m_window = nullptr;
    std::unique_ptr<Camera> m_camera = nullptr;

    void render();
    void update_logic();
};