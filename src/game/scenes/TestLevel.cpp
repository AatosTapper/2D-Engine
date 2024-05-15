#include "TestLevel.h"

#include <memory>

#include "engine/entities/ImageEntity.h"
#include "game/entities/PlayerEntity.h"
#include "engine/Engine.h"

Scene *create_test_level()
{
    Scene *scene = new Scene();

    // all images can share the same texture with this
    std::shared_ptr<Texture> rock_bro = std::make_shared<Texture>("../res/textures/rock.png");

    auto image = CREATE_ENTITY(ImageEntity);
    image->sprite.add_texture(rock_bro);
    image->transform.scale = 4.0f;
    image->transform.z = -60.0f;
    scene->add_entity(std::move(image));

    auto image2 = CREATE_ENTITY(ImageEntity);
    image2->sprite.add_texture(rock_bro);
    image2->transform.scale = 4.0f;
    image2->transform.z = -30.0f;
    image2->transform.x = 4.0f;
    image2->transform.y = 4.0f;
    scene->add_entity(std::move(image2));

    auto image3 = CREATE_ENTITY(ImageEntity);
    image3->sprite.add_texture(rock_bro);
    image3->transform.scale = 4.0f;
    image3->transform.z = -10.0f;
    image3->transform.x = -5.0f;
    image3->transform.y = -4.0f;
    scene->add_entity(std::move(image3));
    
    auto player = CREATE_ENTITY(PlayerEntity);
    scene->add_entity(std::move(player));

    return scene;
}