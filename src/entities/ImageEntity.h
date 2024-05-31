#pragma once

#include "Entity.h"
#include "components/SpriteComponent.h"
#include "components/TransformComponent.h"
#include "components/ColliderComponent.h"

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

