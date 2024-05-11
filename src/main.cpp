#include "config.h"

#include "engine/rendering/Camera.h"
#include "engine/Window.h"
#include "engine/Engine.h"
#include "engine/Scene.h"
#include "engine/gameobjects/ImageGameObject.h"

#include "game/gameobjects/PlayerGameObject.h"

#include "settings.h"

#include <memory>
#include <iostream>

int main()
{
    Engine::init();
    
    Camera camera(Engine::get_window()->get_aspect_ratio(), Settings::CAM_FOV, Settings::CAM_PROJECTION);
    camera.back(10.0f);
    Engine::set_camera(&camera);

    Scene main_scene;
    Engine::set_scene(&main_scene);
    
    std::shared_ptr<Texture> rock_bro = std::make_shared<Texture>("../res/textures/rock.png");

    auto image = CREATE_GAME_OBJECT(ImageGameObject);
    image->sprite.add_texture(rock_bro);
    image->transform.scale = 40.0f;
    image->transform.z = -600.0f;
    main_scene.add_game_object(std::move(image));

    auto image2 = CREATE_GAME_OBJECT(ImageGameObject);
    image2->sprite.add_texture(rock_bro);
    image2->transform.scale = 50.0f;
    image2->transform.z = -300.0f;
    image2->transform.x = 100.0f;
    image2->transform.y = 40.0f;
    main_scene.add_game_object(std::move(image2));

    auto image3 = CREATE_GAME_OBJECT(ImageGameObject);
    image3->sprite.add_texture(rock_bro);
    image3->transform.scale = 80.0f;
    image3->transform.z = -200.0f;
    image3->transform.x = -200.0f;
    image3->transform.y = -40.0f;
    main_scene.add_game_object(std::move(image3));
    
    auto player = CREATE_GAME_OBJECT(PlayerGameObject);
    player->sprite.add_texture(rock_bro);
    main_scene.add_game_object(std::move(player));

    Engine::run();

    return 0;
}