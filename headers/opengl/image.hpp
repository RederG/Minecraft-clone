#ifndef __IMAGE__
    #define __IMAGE__

    #include "../tool.hpp"
    #include "base.hpp"

    namespace gl{
        class Image2D{
            public:
                Image2D(std::string file_path);
                ~Image2D();
                unsigned char* get_data();
                glm::vec2 get_size();
                int get_channels();
            private:
                int width, height, channels;
                unsigned char* data;
                std::string file_path;
        };
    };

#endif