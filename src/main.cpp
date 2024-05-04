#include "config.h"

#include "engine/rendering/Camera.h"
#include "engine/Window.h"
#include "engine/Engine.h"
#include "engine/Scene.h"
#include "engine/gameobjects/ImageGameObject.h"

#include <memory>
#include <iostream>

// settings
constexpr int SCR_WIDTH = 1280;
constexpr int SCR_HEIGHT = 720;
constexpr int FPS_CAP = 60;
constexpr float CAM_FOV = 60.0f;
constexpr bool CAM_PROJECTION = PROJ_3D;

int main()
{
    Engine engine(FPS_CAP);
    Window window(SCR_WIDTH, SCR_HEIGHT);

    Camera camera(window.get_aspect_ratio(), CAM_FOV, CAM_PROJECTION);
    camera.back(12.0f);

    Scene main_scene;
    
    // creating a game object of type ImageGameObject and putting it into the scene
    main_scene.add_game_object(
        CREATE_GAME_OBJECT_WITH_ARGS(ImageGameObject, "../res/textures/rock.png")
    );

    engine.set_window(&window);
    engine.set_camera(&camera);
    engine.set_scene(&main_scene);

    engine.run();

    return 0;
}