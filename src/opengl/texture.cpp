#include "../../headers/opengl/texture.hpp"

namespace gl{

    const std::map<TextureParam::Type, unsigned int> texture_param{
        {TextureParam::Type::Wrap_x,            GL_TEXTURE_WRAP_S},
        {TextureParam::Type::Wrap_y,            GL_TEXTURE_WRAP_T},
        {TextureParam::Type::Wrap_z,            GL_TEXTURE_WRAP_R},
        {TextureParam::Type::Minifiying_filter, GL_TEXTURE_MIN_FILTER},
        {TextureParam::Type::Magnifying_filter, GL_TEXTURE_MAG_FILTER},
    };

    const std::map<TextureParam::Options, unsigned int> texture_param_option{
        {TextureParam::Options::Repeat,                     GL_REPEAT},
        {TextureParam::Options::Mirrored_repeat,            GL_MIRRORED_REPEAT},
        {TextureParam::Options::Clamp_to_edge,              GL_CLAMP_TO_EDGE},
        {TextureParam::Options::Clamp_to_border,            GL_CLAMP_TO_BORDER},
        {TextureParam::Options::Nearest,                    GL_NEAREST},
        {TextureParam::Options::Linear,                     GL_LINEAR},
        {TextureParam::Options::Linear_mipmap_linear,       GL_LINEAR_MIPMAP_LINEAR},
        {TextureParam::Options::Linear_mipmap_nearest,      GL_LINEAR_MIPMAP_NEAREST},
        {TextureParam::Options::Nearest_mipmap_linear,      GL_NEAREST_MIPMAP_LINEAR},
        {TextureParam::Options::Nearest_mipmamp_nearest,    GL_NEAREST_MIPMAP_NEAREST},
    };

    Texture2D::Texture2D(std::string file_path){
        const std::map<int, unsigned int> color_format{
            {3, GL_RGB},
            {4, GL_RGBA},
        };

        this->img_data = new Image2D(file_path);
        Tool_verify(glGenTextures(1, &this->id));
        this->bind();
        Tool_verify(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            this->img_data->get_size().x, 
            this->img_data->get_size().y,
            0,
            color_format.at(this->img_data->get_channels()),
            GL_UNSIGNED_BYTE,
            this->img_data->get_data()
        ));
        Tool_verify(glGenerateMipmap(GL_TEXTURE_2D));
        if(auto_binding())
            this->unbind();
    }

    Texture2D::Texture2D(Image2D& image){
        const std::map<int, unsigned int> color_format{
            {3, GL_RGB},
            {4, GL_RGBA},
        };

        this->img_data = &image;
        Tool_verify(glGenTextures(1, &this->id));
        this->bind();
        Tool_verify(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            color_format.at(this->img_data->get_channels()), 
            this->img_data->get_size().x, 
            this->img_data->get_size().y,
            0,
            color_format.at(this->img_data->get_channels()),
            GL_UNSIGNED_BYTE,
            this->img_data->get_data()
        ));
        Tool_verify(glGenerateMipmap(GL_TEXTURE_2D));
        if(auto_binding())
            this->unbind();
    }

    Texture2D::Texture2D(Image2D* image){
        const std::map<int, unsigned int> color_format{
            {3, GL_RGB},
            {4, GL_RGBA},
        };

        this->img_data = image;
        Tool_verify(glGenTextures(1, &this->id));
        this->bind();
        Tool_verify(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            color_format.at(this->img_data->get_channels()), 
            this->img_data->get_size().x, 
            this->img_data->get_size().y,
            0,
            color_format.at(this->img_data->get_channels()),
            GL_UNSIGNED_BYTE,
            this->img_data->get_data()
        ));
        Tool_verify(glGenerateMipmap(GL_TEXTURE_2D));
        if(auto_binding())
            this->unbind();
    }

    Texture2D::~Texture2D(){
        delete this->img_data;
        this->img_data = nullptr;
        Tool_verify(glDeleteTextures(1, &this->id));
    }

    void Texture2D::set(TextureParam::Type type, TextureParam::Options option){
        if(auto_binding())
            this->bind();
        Tool_verify(glTexParameteri(GL_TEXTURE_2D, texture_param.at(type), texture_param_option.at(option)));
        if(auto_binding())
            this->unbind();
    }

    Image2D* Texture2D::get_image(){
        return this->img_data;
    }

    void Texture2D::bind() const{
        Tool_verify(glBindTexture(GL_TEXTURE_2D, this->id));
    }

    void Texture2D::unbind() const{
        Tool_verify(glBindTexture(GL_TEXTURE_2D, 0));
    }

    MixedTexture2D::MixedTexture2D(std::vector<Image2D*> images){
        this->all_textures.clear();
        for(int i = 0; i < images.size(); i++){
            Texture2D* texture = new Texture2D(images[i]);
            texture->unbind();
            Tool_verify(glActiveTexture(GL_TEXTURE0 + i));
            texture->bind();
            this->all_textures.push_back(texture);
        }
    }

    MixedTexture2D::MixedTexture2D(std::vector<Texture2D*> textures){
        this->all_textures = textures;
        for(int i = 0; i < this->all_textures.size(); i++){
            Texture2D* texture = this->all_textures[i];
            texture->unbind();
            Tool_verify(glActiveTexture(GL_TEXTURE0 + i));
            texture->bind();
        }
    }

    void MixedTexture2D::set(TextureParam::Type type, TextureParam::Options option){
        this->unbind_all();
        for(int i = 0; i < this->all_textures.size(); i++){
            Tool_verify(glActiveTexture(GL_TEXTURE0 + i));
            this->all_textures[i]->bind();
            Tool_verify(glTexParameteri(GL_TEXTURE_2D, texture_param.at(type), texture_param_option.at(option)));
        }
    }

    void MixedTexture2D::set(TextureParam::Type type, TextureParam::Options option, int index){
        this->unbind(index);
        Tool_verify(glActiveTexture(GL_TEXTURE0 + index));
        this->all_textures[index]->bind();
        Tool_verify(glTexParameteri(GL_TEXTURE_2D, texture_param.at(type), texture_param_option.at(option)));
    }

    void MixedTexture2D::add(Image2D* image){
        this->all_textures.push_back(new Texture2D(image));
        this->all_textures[this->all_textures.size() - 1]->unbind();
        Tool_verify(glActiveTexture(GL_TEXTURE0 + this->all_textures.size() - 1));
        this->all_textures[this->all_textures.size() - 1]->bind();
    }

    void MixedTexture2D::add(Texture2D* new_texture){
        this->all_textures.push_back(new_texture);
        new_texture->unbind();
        Tool_verify(glActiveTexture(GL_TEXTURE0 + this->all_textures.size() - 1));
        new_texture->bind();
    }

    void MixedTexture2D::bind(int index) const{
        Tool_verify(glActiveTexture(GL_TEXTURE0 + index));
        this->all_textures[index]->bind();
    }

    void MixedTexture2D::unbind(int index) const{
        Tool_verify(glActiveTexture(GL_TEXTURE0 + index));
        Tool_verify(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void MixedTexture2D::bind_all() const{
        for(int i = 0; i < this->all_textures.size(); i++){
            Tool_verify(glActiveTexture(GL_TEXTURE0 + i));
            this->all_textures[i]->bind();
        }
    }

    void MixedTexture2D::unbind_all() const{
        for(int i = 0; i < this->all_textures.size(); i++){
            Tool_verify(glActiveTexture(GL_TEXTURE0 + i));
            Tool_verify(glBindTexture(GL_TEXTURE_2D, 0));
        }
    }
};