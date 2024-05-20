#include "SceneManager.h"

#include <stdexcept>

#include "game/scenes/TestLevel.h"

void SceneManager::load_scene(const std::string &scene_name)
{
    if (scene_name == "TestLevel")
    {
        m_current_scene = create_test_level();
    }
    // add new scenes here
    else
    {
        std::runtime_error("Cannot load scene \"" + scene_name + "\" check the name and implementation.");
    }
}

void SceneManager::unload_current_scene()
{
    if (m_current_scene)
    {
        delete m_current_scene;
        m_current_scene = nullptr;
    }
}

Ptr<Scene> SceneManager::get_current_scene() const
{
    return Ptr<Scene>(m_current_scene);
}