#include "../../headers/Minecraft/textures.hpp"

namespace Minecraft{

    std::map<BlockType, gl::Texture2D*> all_blocks_texture;

    void init_textures(){
        all_blocks_texture = {
            {BlockType::Grass, new gl::Texture2D("../res/images/grass_block.png")},
        };

        for(auto& block_texture : all_blocks_texture){
            block_texture.second->set(gl::TextureParam::Type::Magnifying_filter, gl::TextureParam::Options::Nearest);
            block_texture.second->set(gl::TextureParam::Type::Minifiying_filter, gl::TextureParam::Options::Nearest);
        }

        Tool::log("Minecraft's textures loaded");
    }

    void terminate_textures(){
        for(auto& texture : all_blocks_texture){
            delete texture.second;
            texture.second = nullptr;
        }
        all_blocks_texture.clear();
    }

    gl::Texture2D* get_texture_of(BlockType block){
        return all_blocks_texture.at(block);
    }
};