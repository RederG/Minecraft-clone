#ifndef __VERTEX_ARRAY__
    #define __VERTEX_ARRAY__

    #include "../tool.hpp"
    #include "vertexBuffer.hpp"
    #include "vertexBufferLayout.hpp"

    namespace gl{
        namespace Buffer{
            class VertexArray{
                public:
                    VertexArray();
                    VertexArray(gl::Buffer::Vertex* vertex_buffer, gl::Buffer::VertexLayout* layout);
                    ~VertexArray();

                    void create();
                    void configure_with(gl::Buffer::Vertex* vertex_buffer, gl::Buffer::VertexLayout* layout);
                    Vertex* get_vertex_buffer();
                    VertexLayout* get_vertex_layout();
                    void bind() const;
                    void unbind() const;
                private:
                    unsigned int id;
                    bool is_created = false;
                    Vertex* vertex_buffer;
                    VertexLayout* layout;
            };
        }
    }

#endif