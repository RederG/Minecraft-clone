#ifndef __RENDERER__
    #define __RENDERER__

    #include "../tool.hpp"
    #include "color.hpp"
    #include "vertexArray.hpp"
    #include "vertexBuffer.hpp"
    #include "shader.hpp"
    #include "indexBuffer.hpp"
    #include "texture.hpp"

    namespace gl{
        namespace Renderer{
            void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::Texture2D* texture, gl::ShaderProgram* shader);
            void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::MixedTexture2D* mixed_texture, gl::ShaderProgram* shader);
            void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::ShaderProgram* shader);
            void clear(gl::Color clear_color = gl::Color(0.0f, 0.0f, 0.0f, 1.0f));
        };
    };

#endif