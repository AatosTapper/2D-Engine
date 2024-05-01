#pragma once

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const VertexBuffer &old);
    ~VertexBuffer();

    void set_data(const void *data, unsigned int size);
    void bind() const;
    void unbind() const;
    void free();

    inline unsigned int get_id() const { return m_id; }

private:
    unsigned int m_id;
    bool m_freed;
};