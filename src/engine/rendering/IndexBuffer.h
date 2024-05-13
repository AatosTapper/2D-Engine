#pragma once

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void set_data(const unsigned int *data, unsigned int count);
    void bind() const;
    void unbind() const;
    void free();

    unsigned int get_elements() const { return m_elements; }

private:
    unsigned int m_id;
    unsigned int m_elements;
    bool m_freed;
};