#include "config.h"

#include "engine/rendering/Camera.h"
#include "engine/Window.h"
#include "engine/Engine.h"
#include "engine/Scene.h"
#include "engine/gameobjects/ImageGameObject.h"
#include "engine/gameobjects/PlayerGameObject.h"
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
    
    std::shared_ptr<Texture> rock_bro = std::make_shared<Texture>("../res/textures/rock.png");

    // creating a game object of type ImageGameObject and putting it into the scene
    auto image = CREATE_GAME_OBJECT(ImageGameObject);
    image->sprite.add_texture(rock_bro);
    main_scene.add_game_object(std::move(image));
    
    auto player = CREATE_GAME_OBJECT(PlayerGameObject);
    player->transform.x = -5.0;
    player->sprite.add_texture(rock_bro);
    main_scene.add_game_object(std::move(player));

    Engine::run();

    return 0;
}