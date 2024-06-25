#include "config.h"

#include "rendering/Camera.h"
#include "Window.h"
#include "Engine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScriptEngine.h"

#include "settings.h"
#include "Ref.h"

#include <memory>
#include <iostream>

int main()
{
    auto lua = ScriptEngine::create_lua_state();
    ScriptEngine::run_script(lua, "../src/scripts/test.lua");
    lua["main"]();

    Engine::instance().init();

    SceneManager::instance().load_scene("test_level");
    Engine::instance().run();
    SceneManager::instance().unload_current_scene();

    return 0;
}