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

    SceneManager::instance().load_scene("TestLevel");
    Engine::instance().run();
    SceneManager::instance().unload_current_scene();

    return 0;
}