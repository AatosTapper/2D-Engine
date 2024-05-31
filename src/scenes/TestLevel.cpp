#include "TestLevel.h"

#include <memory>

#include "entities/PlayerEntity.h"
#include "entities/ImageEntity.h"
#include "entities/StaticEntity.h"
#include "Engine.h"
#include "systems/CameraControllerSystem.h"

Scene *create_test_level()
{
    Scene *scene = new Scene();

    scene->add_system(&CameraControllerSystem::get_base_instance());

    // all images can share the same texture with this
    std::shared_ptr<Texture> rock_bro = std::make_shared<Texture>("../res/textures/rock.png");

    auto image = CREATE_ENTITY(ImageEntity);
    image->sprite.add_texture(rock_bro);
    image->transform.scale = 4.0f;
    image->transform.z = -90.0f;
    image->transform.rotation_rad_x = 0.9f;
    image->transform.rotation_rad_y = 0.2f;
    scene->add_entity(std::move(image));

    auto image2 = CREATE_ENTITY(ImageEntity);
    image2->sprite.add_texture(rock_bro);
    image2->transform.scale = 4.0f;
    image2->transform.z = -40.0f;
    image2->transform.x = 4.0f;
    image2->transform.y = 4.0f;
    image2->transform.rotation_rad_z = -0.7f;
    image2->transform.rotation_rad_y = -0.3f;
    scene->add_entity(std::move(image2));

    auto image3 = CREATE_ENTITY(ImageEntity);
    image3->sprite.add_texture(rock_bro);
    image3->transform.scale = 4.0f;
    image3->transform.z = -10.0f;
    image3->transform.x = -5.0f;
    image3->transform.y = -4.0f;
    image3->transform.rotation_rad_x = 0.4f;
    image3->transform.rotation_rad_y = 0.4f;
    image3->transform.rotation_rad_z = 0.3f;
    scene->add_entity(std::move(image3));

    auto player = CREATE_ENTITY(PlayerEntity);
    player->transform.y = 3.0f;
    scene->add_entity(std::move(player));

    auto wall2 = CREATE_ENTITY(StaticEntity);
    wall2->transform.x = 1.0f;
    wall2->transform.y = -2.5f;
    scene->add_entity(std::move(wall2));

    auto wall1 = CREATE_ENTITY(StaticEntity);
    wall1->transform.x = 6.0f;
    wall1->transform.y = -2.0f;
    scene->add_entity(std::move(wall1));

    auto wall3 = CREATE_ENTITY(StaticEntity);
    wall3->transform.x = -4.0f;
    wall3->transform.y = -3.0f;
    wall3->transform.scale_x = 1.6f;
    wall3->collider.width = 1.6f;
    scene->add_entity(std::move(wall3));

    auto floor = CREATE_ENTITY(StaticEntity);
    floor->transform.x = 18.0f;
    floor->transform.y = -2.0f;
    floor->transform.scale_x = 10.0f;
    floor->collider.width = 10.0f;
    scene->add_entity(std::move(floor));

    return scene;
}