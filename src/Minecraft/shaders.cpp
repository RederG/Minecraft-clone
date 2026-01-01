#include "../../headers/Minecraft/shaders.hpp"

namespace Minecraft{
    gl::ShaderProgram Block_shader;

    void init_shaders(){
        Block_shader.create();
        Block_shader.link_with("../res/shaders/block_vertex_shader.glsl", gl::ShaderType::Vertex);
        Block_shader.link_with("../res/shaders/block_fragment_shader.glsl", gl::ShaderType::Fragment);
        Block_shader.validate();

        Tool::log("Minecraft's shaders initiated");
    }

    void terminate_shaders(){
        Block_shader.~ShaderProgram();
        Tool::log("Minecraft's shaders terminated");
    }
};