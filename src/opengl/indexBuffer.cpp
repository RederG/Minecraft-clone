#include "../../headers/opengl/indexBuffer.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{
    namespace Buffer{
        Index::Index(){}

        Index::Index(const unsigned int* data, const unsigned int index_number)
        : index_number(index_number)
        {
            Tool_verify(glGenBuffers(1, &this->id));
            this->is_created = true;
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_number * sizeof(unsigned int), data, GL_STATIC_DRAW));
            if(gl::auto_binding())
                this->unbind();
        }

        Index::~Index(){
            Tool_verify(glDeleteBuffers(1, &this->id));
        }

        void Index::create(){
            this->is_created = true;
            Tool_verify(glGenBuffers(1, &this->id));
        }

        void Index::set_data(const unsigned int* data, const unsigned int index_number){
            this->bind();
            this->index_number = index_number;
            Tool_verify(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_number * sizeof(unsigned int), data, GL_STATIC_DRAW));
            if(auto_binding())
                this->unbind();
        }

        unsigned int Index::get_index_number() const{
            return this->index_number;
        }

        void Index::bind() const{
            if(!this->is_created)
                Tool::throw_opengl_error("The index buffer is not already created !!", "gl::Buffer::Index::bind()");
            Tool_verify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id));
        }

        void Index::unbind() const{
            if(!this->is_created)
                Tool::throw_opengl_error("The index buffer is not already created !!", "gl::Buffer::Index::unbind()");
            Tool_verify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    }
};