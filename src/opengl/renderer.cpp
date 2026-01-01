#include "../../headers/opengl/renderer.hpp"

namespace gl{
    namespace Renderer{
        void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::Texture2D* texture, gl::ShaderProgram* shader){
            vertex_array->bind();
            shader->use_me();
            texture->bind();
            if(index_buffer != nullptr){
                index_buffer->bind();
                Tool_verify(glDrawElements(GL_TRIANGLES, index_buffer->get_index_number(), GL_UNSIGNED_INT, 0));
            }
            else
                Tool_verify(glDrawArrays(GL_TRIANGLES, 0, vertex_array->get_vertex_buffer()->get_attribute_number(vertex_array->get_vertex_layout())));
        }

        void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::MixedTexture2D* mixed_texture, gl::ShaderProgram* shader){
            vertex_array->bind();
            shader->use_me();
            mixed_texture->bind_all();
            if(index_buffer != nullptr){
                index_buffer->bind();
                Tool_verify(glDrawElements(GL_TRIANGLES, index_buffer->get_index_number(), GL_UNSIGNED_INT, 0));
            }
            else
                Tool_verify(glDrawArrays(GL_TRIANGLES, 0, vertex_array->get_vertex_buffer()->get_attribute_number(vertex_array->get_vertex_layout())));
        }

        void draw(gl::Buffer::VertexArray* vertex_array, gl::Buffer::Index* index_buffer, gl::ShaderProgram* shader){
            vertex_array->bind();
            shader->use_me();
            if(index_buffer != nullptr){
                index_buffer->bind();
                Tool_verify(glDrawElements(GL_TRIANGLES, index_buffer->get_index_number(), GL_UNSIGNED_INT, 0));
            }
            else
                Tool_verify(glDrawArrays(GL_TRIANGLES, 0, vertex_array->get_vertex_buffer()->get_attribute_number(vertex_array->get_vertex_layout())));
        }

        void clear(gl::Color clear_color){
            Tool_verify(glClearColor(
                clear_color.r, 
                clear_color.g, 
                clear_color.b, 
                clear_color.a
            ));
            unsigned int bit = GL_COLOR_BUFFER_BIT;
            if(gl::is_enabled(gl::Options::Depth_testing))
                bit |= GL_DEPTH_BUFFER_BIT;
            Tool_verify(glClear(bit));
        }
    };
}