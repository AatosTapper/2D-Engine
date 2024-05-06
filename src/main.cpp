#include "config.h"

#include "engine/rendering/Camera.h"
#include "engine/Window.h"
#include "engine/Engine.h"
#include "engine/Scene.h"
#include "engine/gameobjects/ImageGameObject.h"
#include "engine/systems/CollisionSystem.h"

#include "settings.h"

#include <memory>
#include <iostream>

int main()
{
    Engine::init();
    
    Camera camera(Engine::get_window()->get_aspect_ratio(), Settings::CAM_FOV, Settings::CAM_PROJECTION);
    Engine::set_camera(&camera);
    camera.back(12.0f);

    Scene main_scene;
    Engine::set_scene(&main_scene);
    
    // creating a game object of type ImageGameObject and putting it into the scene
    main_scene.add_game_object(
        CREATE_GAME_OBJECT_WITH_ARGS(ImageGameObject, "../res/textures/rock.png")
    );

    main_scene.add_system(CollisionSystem::get_base_instance());

    Engine::run();

    return 0;
}