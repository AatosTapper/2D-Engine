#pragma once

#include <string>

#include "Scene.h"
#include "Ref.h"
#include "singleton.h"

class SceneManager
{
public:
    ~SceneManager() { unload_current_scene(); }

    void load_scene(const std::string_view &name);           // unloads the last current scene
    void unload_current_scene();
    [[nodiscard]] Ptr<Scene> get_current_scene() const;

    void switch_to_temp_scene(const std::string_view &name); // keeps the current scene in memory
    void unload_temp_scene();

    IMPL_SINGLETON_DISPATCHER(SceneManager)
    IMPL_NO_COPY(SceneManager)

private:
    SceneManager() {}

    Scene *m_current_scene = nullptr;
    Scene *m_cached_scene = nullptr;
};
