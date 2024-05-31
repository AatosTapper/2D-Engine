#include "VertexBuffer.h"

#include "config.h"

#include <stdio.h>

#define CHECK() \
do { \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        fprintf(stderr, "OpenGL Error (%s:%d): %d\n", __FILE__, __LINE__, error); \
    } \
} while (false)

VertexBuffer::VertexBuffer() : m_freed(false)
{
    
}

VertexBuffer::VertexBuffer(const VertexBuffer &old)
{
    m_id = old.m_id;
    m_freed = old.m_freed;
}

VertexBuffer::~VertexBuffer()
{
    if (!m_freed)
        glDeleteBuffers(1, &m_id);
}

void VertexBuffer::set_data(const void *data, unsigned int size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::free()
{
    if (!m_freed)
    {
        glDeleteBuffers(1, &m_id);
        m_freed = true;
    }
}