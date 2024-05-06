#include "ImageGameObject.h"

#include "../Engine.h"
#include "../rendering/Renderer.h"
#include "../systems/CollisionSystem.h"

ImageGameObject::ImageGameObject()
{

}

ImageGameObject::ImageGameObject(const char *texture_path)
{
    sprite.transform.scale = 1.0f;
    sprite.add_texture(texture_path);
}

void ImageGameObject::on_attach()
{
    sprite.get_texture()->filter_nearest();
}

void ImageGameObject::update_components()
{
    glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    Renderer::instance().queue_sprite({ &sprite, full_transform });
}

void ImageGameObject::on_update()
{
    // THIS IS FOR TESTING
    
    transform.scale_x = 1.0f + (float)sin(glfwGetTime() * 1.5f) * 0.05f;
    transform.scale_y = 1.0f + (float)sin(glfwGetTime() * 1.5f) * -0.05f;
}

void ImageGameObject::on_destroy()
{
    // nothing here now
}