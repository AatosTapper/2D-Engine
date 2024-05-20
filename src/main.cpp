#include "config.h"

#include "engine/rendering/Camera.h"
#include "engine/Window.h"
#include "engine/Engine.h"
#include "engine/Scene.h"
#include "engine/SceneManager.h"

#include "settings.h"
#include "Ref.h"

#include <memory>
#include <iostream>

int main()
{
    Engine::instance().init();
    
    Camera camera(Engine::instance().get_window()->get_aspect_ratio(), Settings::CAM_FOV, Settings::CAM_PROJECTION);
    camera.back(20.0f);
    
    Engine::instance().set_camera(&camera);
    SceneManager::instance().load_scene("TestLevel");
    Engine::instance().run();
    SceneManager::instance().unload_current_scene();

    return 0;
}