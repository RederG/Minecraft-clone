#ifndef __VERTEX_BUFFER__
    #define __VERTEX_BUFFER__

    #include "../tool.hpp"
    #include "vertexBufferLayout.hpp"

    namespace gl{
        namespace Buffer{
            class Vertex{
                public:
                    Vertex(const void* data, const int size);
                    Vertex();
                    ~Vertex();

                    void set_data(const void* data, const int size);
                    void create();
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, float* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, int* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned int* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, double* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, bool* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, char* new_data, int data_number);
                    void set_subdata(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, unsigned char* new_data, int data_number);

                    unsigned int get_attribute_number(VertexLayout* layout);
                    void bind() const;
                    void unbind() const;
                private:
                    unsigned int id;
                    unsigned int data_size;
                    bool is_created = false;
                    signed long long get_offset(VertexType type, unsigned int rank, unsigned int position, VertexLayout* layout, Type data_type);
                    bool verify_data_number(VertexType type, unsigned int position, VertexLayout* layout, int size);
                    bool verify_data_type(VertexType type, VertexLayout* layout, gl::Type gl_type);
                    bool verify_position(VertexType type, VertexLayout* layout, unsigned int position);
                    bool verify_rank(VertexType type, VertexLayout* layout, unsigned int rank);
            };
        }
    }

#endif