#pragma once

#include <string>

#include "engine/Scene.h"
#include "Ref.h"
#include "singleton.h"

class SceneManager
{
public:
    ~SceneManager() { unload_current_scene(); }
    void load_scene(const std::string &scene_name);
    void unload_current_scene();
    Ptr<Scene> get_current_scene() const;

    IMPL_SINGLETON_DISPATCHER(SceneManager)
    IMPL_NO_COPY(SceneManager)

private:
    SceneManager() {}

    Scene *m_current_scene = nullptr;
};
