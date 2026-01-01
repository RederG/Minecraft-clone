#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../../headers/opengl/image.hpp"

namespace gl{
    Image2D::Image2D(std::string file_path){
        if(!std::filesystem::exists(file_path))
            Tool::throw_opengl_error("Image file does not exist", "Image::Image(std::string file_path)");
        stbi_set_flip_vertically_on_load(true);
        this->file_path = file_path;
        this->data = stbi_load(this->file_path.c_str(), &this->width, &this->height, &this->channels, 0);
    }

    Image2D::~Image2D(){
        delete[] this->data;
        this->data = nullptr;
    }

    glm::vec2 Image2D::get_size(){
        glm::vec2 size;
        size.x = this->width;
        size.y = this->height;
        return size;
    }

    int Image2D::get_channels(){
        return this->channels;
    }

    unsigned char* Image2D::get_data(){
        return this->data;
    }
};