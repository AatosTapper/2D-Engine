#pragma once

#include "../GameObject.h"
#include "../rendering/Sprite.h"
#include "../rendering/Renderer.h"
#include "../Window.h"
#include "../components/TransformComponent.h"

#include "../Scene.h"

class ImageGameObject : public GameObject
{
public:
    ImageGameObject(const char *texture_path);

    Sprite sprite;
    Transform3DComponent transform;

    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

