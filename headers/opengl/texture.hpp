#ifndef __TEXTURE_2D__
    #define __TEXTURE_2D__

    #include "../tool.hpp"
    #include "image.hpp"

    namespace gl{
        namespace TextureParam{
            enum Type{
                Wrap_x, Wrap_y, Wrap_z, Minifiying_filter, Magnifying_filter
            };

            enum Options{
                Repeat, Mirrored_repeat, Clamp_to_edge, Clamp_to_border, Nearest, Linear, 
                Linear_mipmap_linear, Linear_mipmap_nearest, Nearest_mipmap_linear, Nearest_mipmamp_nearest
            };
        };

        class Texture2D{
            public:
                Texture2D(std::string file_path);
                Texture2D(Image2D& image);
                Texture2D(Image2D* image);
                ~Texture2D();
                
                Image2D* get_image();
                void set(TextureParam::Type type, TextureParam::Options option);

                void bind() const;
                void unbind() const;
            private:
                unsigned int id;
                Image2D* img_data;
        };

        class MixedTexture2D{
            public:
                MixedTexture2D(std::vector<Image2D*> images);
                MixedTexture2D(std::vector<Texture2D*> textures);
                void set(TextureParam::Type type, TextureParam::Options option);
                void set(TextureParam::Type type, TextureParam::Options option, int index);

                void add(Image2D* new_image);
                void add(Texture2D* new_texture);

                void bind(int index = 0) const;
                void unbind(int index = 0) const;
                void bind_all() const;
                void unbind_all() const;
            private:
                unsigned int id;
                std::vector<Texture2D*> all_textures;
        };
    };

#endif