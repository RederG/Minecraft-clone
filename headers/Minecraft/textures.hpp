#ifndef __TEXTURES_HPP__
    #define __TEXTURES_HPP__

    #include "../tool.hpp"
    #include "block.hpp"

    namespace Minecraft{
        void init_textures();
        void terminate_textures();
        gl::Texture2D* get_texture_of(BlockType block);
    };

#endif