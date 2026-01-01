#include "../../headers/opengl/vertexBuffer.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{
    namespace Buffer{

        Vertex::Vertex(){}

        Vertex::Vertex(const void* data, const int size){
            Tool_verify(glGenBuffers(1, &this->id));
            this->bind();
            Tool_verify(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            this->data_size = size;
            this->is_created = true;
            if(gl::auto_binding())
                this->unbind();
        }

        Vertex::~Vertex(){
            Tool_verify(glDeleteBuffers(1, &this->id));
        }

        signed long long Vertex::get_offset(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, Type data_type){
            signed long long offset = 0;
            const std::vector<VertexElements> verteces = layout->get_all_verteces();
            for(int i = 0; i < verteces.size(); i++){
                if(verteces[i].type == type){
                    if(verteces[i].gl_type == gl::data_type.at(data_type))
                        break;
                }
                offset += verteces[i].get_size();
            }
            offset += layout->get_stride() * rank + position * get_size_of(gl::data_type.at(data_type));
            return offset;
        }

        bool Vertex::verify_data_number(VertexType type, unsigned int position, VertexLayout* layout, int data_number){
            const std::vector<VertexElements> verteces = layout->get_all_verteces();
            for(int i = 0; i < verteces.size(); i++){
                if(verteces[i].type == type && (data_number) <= verteces[i].number && position <= (verteces[i].number - 1))
                    return true;
            }
            return false;
        }

        bool Vertex::verify_data_type(VertexType type, VertexLayout* layout, gl::Type gl_type){
            const std::vector<VertexElements> verteces = layout->get_all_verteces();
            for(int i = 0; i < verteces.size(); i++){
                if(verteces[i].type == type && verteces[i].gl_type == gl::data_type.at(gl_type))
                    return true;
            }
            return false;
        }

        bool Vertex::verify_position(VertexType type, VertexLayout* layout, unsigned int position){
            const std::vector<VertexElements> verteces = layout->get_all_verteces();
            for(int i = 0; i < verteces.size(); i++){
                if(verteces[i].type == type && position <= (verteces[i].number - 1))
                    return true;
            }
            return false;
        }

        bool Vertex::verify_rank(VertexType type, VertexLayout* layout, unsigned int rank){
            if(rank <= (this->data_size/layout->get_stride() - 1))
                return true;
            return false;
        }

        void Vertex::create(){
            if(!this->is_created){
                Tool_verify(glGenBuffers(1, &this->id));
                this->data_size = 0;
                this->is_created = true;
            }
            else
                Tool::throw_opengl_error("The vertex buffer is already created !", "gl::Buffer::Vertex::create()");
        }

        void Vertex::set_data(const void* data, const int size){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_data(const void* data, const int size)");
            this->bind();
            Tool_verify(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            this->data_size = size;
            if(auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, float* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, float* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, float* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, float* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Float)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" must be a float*", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, float* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Float);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, float* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(float)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, int* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, int* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, int* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, int* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Int)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, int* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Int);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, int* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(int)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned int* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned int* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned int* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned int* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Uint)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned int* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Uint);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned int* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(unsigned int)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, double* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, double* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, double* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, double* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Double)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, double* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Double);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, double* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(double)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, bool* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, bool* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, bool* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, bool* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Bool)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, bool* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Bool);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, bool* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(bool)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, char* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, char* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, char* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, char* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Char)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, char* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Char);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, char* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(char)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        void Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned char* new_data, int data_number){
            if(!this->is_created)
                Tool::throw_opengl_error("The vertex is not already created !!", "void gl::Buffer::Vertex::set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned char* new_data, int data_number)");
            if(!this->verify_position(type, layout, position)){
                Tool::throw_opengl_error(
                    "Invalid position : the \"position\" is outside the attribute", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned char* new_data, int data_number)"
                );
            }
            if(!this->verify_rank(type, layout, rank)){
                Tool::throw_opengl_error(
                    "Invalid rank : the \"rank\" is outside the data", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned char* new_data, int data_number)"
                );
            }
            if(!this->verify_data_type(type, layout, gl::Type::Uchar)){
                Tool::throw_opengl_error(
                    "Invalid value : the \"new_data\" has not the same type on the layout", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned char* new_data, int data_number)"
                );
            }
            signed long long offset = this->get_offset(type, rank, position, layout, Type::Uchar);
            if(!this->verify_data_number(type, position, layout, data_number)){
                Tool::throw_opengl_error(
                    "Invalid size : the \"new_data\" is too big", 
                    "gl::Buffer::Vertex::set(VertexType type, unsigned int rank, unsigned int position, VertexLayout layout, unsigned char* new_data, int data_number)"
                );
            }
            if(gl::auto_binding())
                this->bind();
            Tool_verify(glBufferSubData(
                GL_ARRAY_BUFFER,
                offset,
                sizeof(unsigned char)*data_number,
                reinterpret_cast<const void*>(new_data)
            ));
            if(gl::auto_binding())
                this->unbind();
        }

        unsigned int Vertex::get_attribute_number(VertexLayout* layout){
            return this->data_size/layout->get_stride();
        }

        void Vertex::bind() const{
            Tool_verify(glBindBuffer(GL_ARRAY_BUFFER, this->id));
        }

        void Vertex::unbind() const{
            Tool_verify(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }
    
    }
}