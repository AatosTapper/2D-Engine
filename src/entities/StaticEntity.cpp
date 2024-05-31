#include "StaticEntity.h"

#include "systems/PhysicsSystem.h"
#include "rendering/Renderer.h"

#include <iostream>

void StaticEntity::on_attach() 
{
    animation.set_fps(6);
    animation.push_folder_as_frames("../res/animations/test_anim");
    animation.set_frame(1);
    animation.play(AnimSpriteComponent::PlaybackType::LOOP);
    

    physics.set_flags(PhysicsFlags::STATIC);
}

void StaticEntity::update_components() 
{
    if (has_state_flags(EntityStateFlags::IS_SUPPORTING))
    {
        animation.stop();
    }
    else
    {
        animation.play(AnimSpriteComponent::PlaybackType::LOOP);
    }
    
    animation.update(transform.get_matrix());

    //std::cout << "Updated entity " << get_id() << "\n";

    PhysicsSystem::instance().queue_entity({ this, physics, &collider, transform });
}
