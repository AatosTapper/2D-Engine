#include "SceneManager.h"

#include "game/scenes/TestLevel.h"

void SceneManager::load_scene(const std::string &scene_name)
{
    if (scene_name == "TestLevel")
    {
        current_scene = load_test_level();
    }
}

void SceneManager::unload_current_scene()
{
    if (current_scene)
    {
        delete current_scene;
        current_scene = nullptr;
    }
}

Ptr<Scene> SceneManager::get_current_scene() const
{
    return Ptr<Scene>(current_scene);
}