#ifndef __WORLD_HPP__
    #define __WORLD_HPP__

    #include "../tool.hpp"
    #include "block.hpp"

    namespace Minecraft{
        class Chunck;
        class Entity;

        class World{
            public:
                World(int render_distance, glm::vec3 chunck_size);
                void draw_to(GLFWwindow* window, glm::mat4 camera_view);
                void update(glm::vec3 position);
                BlockType get_block(glm::vec3 position);
            private:
                glm::vec3 chunck_size;
                std::vector<Chunck*> all_chuncks;
                std::vector<Chunck*> all_current_chuncks;
                int render_distance;
        };
    };

#endif