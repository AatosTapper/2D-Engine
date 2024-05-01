#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
    VertexArray();
    VertexArray(const VertexArray &old);
    ~VertexArray();

    void add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void bind() const;
    void unbind() const;
    void free();

    inline unsigned int get_id() const { return m_id; }
    
private:
    unsigned int m_id;
    bool m_freed;
};