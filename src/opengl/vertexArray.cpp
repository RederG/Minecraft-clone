#include "../../headers/opengl/vertexArray.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{
    namespace Buffer{
        VertexArray::VertexArray(){}

        VertexArray::VertexArray(gl::Buffer::Vertex* vertex_buffer, gl::Buffer::VertexLayout* layout){
            Tool_verify(glGenVertexArrays(1, &this->id));
            this->configure_with(vertex_buffer, layout);
            this->is_created = true;
        }

        VertexArray::~VertexArray(){
            Tool_verify(glDeleteVertexArrays(1, &this->id));
        }

        void VertexArray::create(){
            if(!this->is_created){
                Tool_verify(glGenVertexArrays(1, &this->id));
                this->is_created = true;
            }
            else
                Tool::throw_opengl_error("The vertex array is already created !!", "gl::VertexArray::create()");
        }

        void VertexArray::configure_with(gl::Buffer::Vertex* vertex_buffer, gl::Buffer::VertexLayout* layout){
            vertex_buffer->bind();
            this->bind();
            unsigned int offset = 0;
            for(unsigned int i = 0; i < layout->get_all_verteces().size(); i++){
                gl::VertexElements vertex_elements = layout->get_all_verteces()[i];
                Tool_verify(glEnableVertexAttribArray(i));
                Tool_verify(glVertexAttribPointer(
                    i, 
                    vertex_elements.number, 
                    vertex_elements.gl_type, 
                    vertex_elements.normalized, 
                    layout->get_stride(), 
                    reinterpret_cast<const void*>(offset)
                ));
                offset += vertex_elements.get_size();
            }
            if(gl::auto_binding()){
                this->unbind();
                vertex_buffer->unbind();
            }
            this->vertex_buffer = vertex_buffer;
            this->layout = layout;
        }

        Vertex* VertexArray::get_vertex_buffer(){
            return this->vertex_buffer;
        }

        VertexLayout* VertexArray::get_vertex_layout(){
            return this->layout;
        }

        void VertexArray::bind() const{
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex array is not already created !!", "gl::VertexArray::bind()");
            Tool_verify(glBindVertexArray(this->id));
        }

        void VertexArray::unbind() const{
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex array is not already created !!", "gl::VertexArray::unbind()");
            Tool_verify(glBindVertexArray(0));
        }
    }
}