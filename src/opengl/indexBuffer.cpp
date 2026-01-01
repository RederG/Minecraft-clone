#include "../../headers/opengl/indexBuffer.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{
    namespace Buffer{
        Index::Index(const unsigned int* data, const unsigned int index_number)
        : index_number(index_number)
        {
            Tool_verify(glGenBuffers(1, &this->id));
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_number * sizeof(unsigned int), data, GL_STATIC_DRAW));
            if(gl::auto_binding())
                this->unbind();
        }

        Index::~Index(){
            Tool_verify(glDeleteBuffers(1, &this->id));
        }

        unsigned int Index::get_index_number() const{
            return this->index_number;
        }

        void Index::bind() const{
            Tool_verify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id));
        }

        void Index::unbind() const{
            Tool_verify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    }
};