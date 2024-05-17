#include "StaticEntity.h"

#include "engine/systems/PhysicsSystem.h"
#include "engine/rendering/Renderer.h"

#include <iostream>

void StaticEntity::on_attach() 
{
    animation.set_fps(10);
    animation.push_folder_as_frames("../res/animations/test_anim");
    animation.set_frame(1);
    //animation.play(AnimSpriteComponent::PlaybackType::LOOP);

    physics.mass = 10.0f;
}

void StaticEntity::update_components() 
{
    animation.update(transform.get_matrix());

    //std::cout << "Updated entity " << get_id() << "\n";

    PhysicsSystem::instance().queue_entity({ physics, &collider, transform });
}
