#include "../../headers/opengl/vertexBufferLayout.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{   

    unsigned int VertexElements::get_size() const{
        return this->number * get_size_of(this->gl_type);
    }

    namespace Buffer{ 

        VertexLayout::VertexLayout(){
            this->all_verteces.clear();
            this->stride = 0;
        }

        void VertexLayout::add(unsigned int number, Type value_type, bool gl_normalized, VertexType type){
            VertexElements vertex;
            vertex.number = number;
            unsigned int gl_type;
            switch (value_type){
                case Type::Bool:
                    gl_type = GL_BOOL;
                    break;
                case Type::Float:
                    gl_type = GL_FLOAT;
                    break;
                case Type::Int:
                    gl_type = GL_INT;
                    break;
                case Type::Uint:
                    gl_type = GL_UNSIGNED_INT;
                    break;
                case Type::Char:
                    gl_type = GL_BYTE;
                    break;
                case Type::Uchar:
                    gl_type = GL_UNSIGNED_BYTE;
                    break;
                default:
                    break;
            }
            vertex.gl_type = gl_type;
            vertex.normalized = (gl_normalized == true) ? GL_TRUE : GL_FALSE;
            vertex.type = type;
            this->all_verteces.push_back(vertex);
            this->stride += vertex.get_size();
        }

        const std::vector<VertexElements> VertexLayout::get_all_verteces(){
            return this->all_verteces;
        }

        unsigned int VertexLayout::get_stride(){
            return this->stride;
        }
    }
}