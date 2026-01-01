#ifndef __CHUNCK_HPP__
    #define __CHUNCK_HPP__

    #include "../tool.hpp"
    #include "block.hpp"
    #include "minecraft.hpp"

    namespace Minecraft{
        class World;
        
        class Chunck{
            public:
                Chunck(glm::vec2 position, glm::vec3 size);
                void fill();
                void update(World* world);
                void draw_to(GLFWwindow* window, glm::mat4* camera_view, World* world);
                bool is_mine(glm::vec3 block_pos);
                glm::vec2 get_position();
                BlockType get_block(glm::vec3 position);
            private:
                glm::vec2 position;
                glm::vec3 size;
                std::vector<BlockType> all_blocks;
                std::vector<BlockDrawableFace> all_drawable_faces;
        };
    };

#endif