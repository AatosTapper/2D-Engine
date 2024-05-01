#pragma once

#include <string>

// TODO: resizing
// TODO: selectable texture filtering

class Texture
{
public:
    Texture(const std::string &file, bool flip = false); // flip parameter is for certain file formats
    ~Texture();

    void bind();
    void unbind();
    void free();

private:
    unsigned int m_id;
    bool m_freed;
};
