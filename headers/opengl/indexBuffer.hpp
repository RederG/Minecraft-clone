#ifndef __INDEX_BUFFER__
    #define __INDEX_BUFFER__

    #include "../tool.hpp"

    namespace gl{
        namespace Buffer{
            class Index{
                public:
                    Index();
                    Index(const unsigned int* data, const unsigned int index_number);
                    ~Index();

                    void create();
                    void set_data(const unsigned int* data, const unsigned int index_number);

                    unsigned int get_index_number() const;

                    void bind() const;
                    void unbind() const;
                private:
                    unsigned int id;
                    int index_number;
                    bool is_created = false;
            };
        }
    }

#endif