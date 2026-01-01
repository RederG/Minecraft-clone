#ifndef __SHADERS_HPP__
    #define __SHADERS_HPP__

    #include "../opengl/opengl.hpp"

    namespace Minecraft{
        extern gl::ShaderProgram Block_shader;

        void init_shaders();
        void terminate_shaders();
    };

#endif