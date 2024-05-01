#include "IndexBuffer.h"

#include "../../config.h"

IndexBuffer::IndexBuffer() : m_freed(false), m_elements(0)
{
     
}

IndexBuffer::~IndexBuffer()
{
    if (!m_freed)
        glDeleteBuffers(1, &m_id);
}

void IndexBuffer::set_data(unsigned int *data, unsigned int count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    m_elements = count;
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::free()
{
    if (!m_freed)
    {
        glDeleteBuffers(1, &m_id);
        m_freed = true;
    }
}