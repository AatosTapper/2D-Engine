#include "ImageEntity.h"

#include "Engine.h"
#include "rendering/Renderer.h"

ImageEntity::ImageEntity()
{

}

ImageEntity::ImageEntity(const char *texture_path)
{
    sprite.add_texture(texture_path);
}

void ImageEntity::on_attach()
{
    // set texture filtering here to avoid problems with uninitialized textures
    sprite.get_texture()->filter_nearest();
}

void ImageEntity::update_components()
{
    glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    Renderer::instance().queue_sprite({ sprite, full_transform });
}