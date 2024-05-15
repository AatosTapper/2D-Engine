#pragma once

#include "engine/Entity.h"
#include "engine/components/SpriteComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/ColliderComponent.h"

class ImageEntity : public Entity
{
public:
    ImageEntity(const char *texture_path);
    ImageEntity();

    Transform3DComponent transform;
    SpriteComponent sprite;

    void update_components() override;
    void on_attach() override;
};

