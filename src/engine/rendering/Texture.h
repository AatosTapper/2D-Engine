#pragma once

#include <string>

// TODO: resizing

class Texture
{
public:
    Texture(const std::string &file, bool flip = false);
    ~Texture();

    void bind();
    void unbind();
    void free();

private:
    unsigned int m_id;
    bool m_freed;
};
