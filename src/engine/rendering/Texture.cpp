#include "Texture.h"

#include "../../config.h"
#include "../../util.h"

#ifndef STB_IMAGE_INCLUDE_H
    #define STB_IMAGE_INCLUDE_H
    #define STB_IMAGE_IMPLEMENTATION // This can be only defined once
    #include <STB/stb_image.h>
#endif

Texture::Texture(const std::string &file, bool flip) : m_freed(false)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int img_width, img_height, img_channels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *image = stbi_load(file.c_str(), &img_width, &img_height, &img_channels, 0);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ERR("Failed to load texture " << file);
    }

    stbi_image_free(image);
}

Texture::~Texture()
{
    if (!m_freed)
    {
        glDeleteTextures(1, &m_id);
    }
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::free()
{
    if (!m_freed)
    {
        glDeleteTextures(1, &m_id);
        m_freed = true;
    }
}