#include "Texture.h"

#include "config.h"
#include "util.h"

#include <algorithm>

#ifndef STB_IMAGE_INCLUDE_H
    #define STB_IMAGE_INCLUDE_H
    #define STB_IMAGE_IMPLEMENTATION // This can be only defined once
    #include <STB/stb_image.h>
#endif

static bool is_png(const std::string &path);

Texture::Texture(const std::string &file) : m_freed(false)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    const bool png = is_png(file);

    int img_width, img_height, img_channels;
    stbi_set_flip_vertically_on_load(png); // pngs need to be flipped
    unsigned char *image = stbi_load(file.c_str(), &img_width, &img_height, &img_channels, 0);

    GLint gl_channels = png ? GL_RGBA : GL_RGB;

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, gl_channels, img_width, img_height, 0, (GLenum)gl_channels, GL_UNSIGNED_BYTE, image);
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

void Texture::filter_nearest()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::filter_linear()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool is_png(const std::string &path)
{
    size_t dot_pos = path.find_last_of('.');
    if (dot_pos != std::string::npos)
    {
        std::string extension = path.substr(dot_pos + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        return extension == "png";
    }
    return false;
}