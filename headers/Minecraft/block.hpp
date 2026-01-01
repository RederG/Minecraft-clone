#ifndef __BLOCK_HPP__
    #define __BLOCK_HPP__

    #include "../opengl/opengl.hpp"
    #include "buffers.hpp"
    #include "shaders.hpp"

    namespace Minecraft{
        enum BlockType{
            Air, Grass
        };

        struct BlockDrawableFace{
            bool    front   = true, back = true,
                    right   = true, left = true,
                    up      = true, down = true;
        };

        class Block{
            public:
                Block();
                Block(glm::vec3 position, BlockType type);
                void draw_to(GLFWwindow* window, glm::mat4* camera_view, BlockDrawableFace* drawable_faces);
            private:
                glm::vec3 position;
                BlockType type;
        };
    };

#endif