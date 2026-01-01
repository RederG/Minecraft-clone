#ifndef __INDEX_BUFFER__
    #define __INDEX_BUFFER__

    #include "../tool.hpp"

    namespace gl{
        namespace Buffer{
            class Index{
                public:
                    Index(const unsigned int* data, const unsigned int index_number);
                    ~Index();

                    unsigned int get_index_number() const;

                    void bind() const;
                    void unbind() const;
                private:
                    unsigned int id;
                    int index_number;
            };
        }
    }

#endif