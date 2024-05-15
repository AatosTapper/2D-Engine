#pragma once

#include <string>

#include "engine/Scene.h"
#include "Ref.h"
#include "singleton.h"

class SceneManager
{
public:
    void load_scene(const std::string &scene_name);
    void unload_current_scene();
    Ptr<Scene> get_current_scene() const;

    IMPL_SINGLETON_DISPATCHER(SceneManager)
    IMPL_NO_COPY(SceneManager)

private:
    SceneManager() {}

    Scene *current_scene = nullptr;
};
