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

public:
    Texture(const Texture&) = delete;
    Texture(Texture&& other) 
    {
        other.m_id = m_id;
        other.m_freed = m_freed;
    }
};
