#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string &file); // flip parameter is for certain file formats
    ~Texture();

    void bind() const;
    void unbind() const;
    void free();

    void filter_nearest(); // pixelated look
    void filter_linear();  // normal filtering

private:
    unsigned int m_id;
    bool m_freed;
};
