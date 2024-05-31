#include "SceneManager.h"

#include <stdexcept>

#include "scenes/TestLevel.h"

static void assign_scene(Scene **ptr, const std::string_view &name)
{
    if (name == "test_level")
    {
        *ptr = create_test_level();
    }
    // add new scenes here
    else
    {
        std::runtime_error("No matching scene \"" + std::string(name) + "\". Check the name and implementation.");
        ptr = nullptr;
    }
}

void SceneManager::load_scene(const std::string_view &name)
{
    unload_current_scene();
    assign_scene(&m_current_scene, name);
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

void SceneManager::switch_to_temp_scene(const std::string_view &name)
{
    if (m_cached_scene)
    {
        delete m_cached_scene;
        m_cached_scene = nullptr;
    }
    m_cached_scene = m_current_scene;
    assign_scene(&m_current_scene, name);
}

void SceneManager::unload_temp_scene()
{
    m_current_scene = m_cached_scene;
    m_cached_scene = nullptr;
}
