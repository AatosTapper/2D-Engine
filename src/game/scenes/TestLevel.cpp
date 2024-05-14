#include "TestLevel.h"

#include <memory>

#include "engine/gameobjects/ImageGameObject.h"
#include "game/gameobjects/PlayerGameObject.h"
#include "engine/Engine.h"

Scene *load_test_level()
{
    Scene *scene = new Scene();

    std::shared_ptr<Texture> rock_bro = std::make_shared<Texture>("../res/textures/rock.png");

    auto image = CREATE_GAME_OBJECT(ImageGameObject);
    image->sprite.add_texture(rock_bro);
    image->transform.scale = 4.0f;
    image->transform.z = -60.0f;
    scene->add_game_object(std::move(image));

    auto image2 = CREATE_GAME_OBJECT(ImageGameObject);
    image2->sprite.add_texture(rock_bro);
    image2->transform.scale = 4.0f;
    image2->transform.z = -30.0f;
    image2->transform.x = 4.0f;
    image2->transform.y = 4.0f;
    scene->add_game_object(std::move(image2));

    auto image3 = CREATE_GAME_OBJECT(ImageGameObject);
    image3->sprite.add_texture(rock_bro);
    image3->transform.scale = 4.0f;
    image3->transform.z = -10.0f;
    image3->transform.x = -5.0f;
    image3->transform.y = -4.0f;
    scene->add_game_object(std::move(image3));
    
    auto player = CREATE_GAME_OBJECT(PlayerGameObject);
    player->sprite.add_texture(rock_bro);
    scene->add_game_object(std::move(player));

    return scene;
}