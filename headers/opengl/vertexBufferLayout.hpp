#ifndef __VERTEX_BUFFER_LAYOUT__
    #define __VERTEX_BUFFER_LAYOUT__

    #include "../tool.hpp"
    #include "base.hpp"

    namespace gl{
        namespace Buffer{
            enum VertexType{
                Position, TextureCoords, Color
            };
        };

        struct VertexElements{
            unsigned int number;
            unsigned int gl_type;
            unsigned int normalized;
            Buffer::VertexType type;
            unsigned int get_size() const;
        };

        namespace Buffer{
            
            class VertexLayout{
                public:
                    VertexLayout();
                    void add(unsigned int number, Type value_type, bool normalized, VertexType type);
                    const std::vector<VertexElements> get_all_verteces();
                    unsigned int get_stride();
                private:
                    std::vector<VertexElements> all_verteces;
                    unsigned int stride;
            };
        }
    }

#endif