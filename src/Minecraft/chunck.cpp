#include "../../headers/Minecraft/chunck.hpp"
#include "../../headers/Minecraft/world.hpp"

namespace Minecraft{
    unsigned int get_index(glm::vec3 block_position, glm::vec3 size){
        int x = abs(int(block_position.x) % int(size.x));
        int z = abs(int(block_position.z) % int(size.y));
        int y = abs(int(block_position.y) % int(size.z));
        unsigned int index = (y * (size.x * size.y)) + (size.x * z + x);
        return index;
    }

    Chunck::Chunck(glm::vec2 pos, glm::vec3 size)
    : position(pos), size(size){
        this->fill();
    }

    void Chunck::fill(){
        for(int z = 0; z < this->size.z; z++){
            for(int y = 0; y < this->size.y; y++){
                for(int x = 0; x < this->size.x; x++){
                    if(z <= this->size.z / 2)
                        this->all_blocks.push_back(BlockType::Grass);
                    else
                        this->all_blocks.push_back(BlockType::Air);
                    this->all_drawable_faces.push_back({true, true, true, true, true, true});
                }
            }
        }
    }

    void Chunck::update(World* world){
        int i = 0;
        for(int z = 0; z < this->size.z; z++){
            for(int y = 0; y < this->size.y; y++){
                for(int x = 0; x < this->size.x; x++){
                    glm::vec3 block_pos = {
                        this->position.x * this->size.x + x,
                        z,
                        this->position.y * this->size.y + y,
                    };

                    if(world->get_block({block_pos.x - 1, block_pos.y, block_pos.z}) != BlockType::Air)
                        this->all_drawable_faces[i].left = false;
                    if(world->get_block({block_pos.x + 1, block_pos.y, block_pos.z}) != BlockType::Air)
                        this->all_drawable_faces[i].right = false;
                    if(world->get_block({block_pos.x, block_pos.y - 1, block_pos.z}) != BlockType::Air)
                        this->all_drawable_faces[i].down = false;
                    if(world->get_block({block_pos.x, block_pos.y + 1, block_pos.z}) != BlockType::Air)
                        this->all_drawable_faces[i].up = false;
                    if(world->get_block({block_pos.x, block_pos.y, block_pos.z - 1}) != BlockType::Air)
                        this->all_drawable_faces[i].back = false;
                    if(world->get_block({block_pos.x, block_pos.y, block_pos.z + 1}) != BlockType::Air)
                        this->all_drawable_faces[i].front = false;
                    i++;
                }
            }
        }
    }

    void Chunck::draw_to(GLFWwindow* window, glm::mat4* camera_view, World* world){
        int i = 0;
        for(int z = 0; z < this->size.z; z++){
            for(int y = 0; y < this->size.y; y++){
                for(int x = 0; x < this->size.x; x++){
                    glm::vec3 block_pos = {
                        this->position.x * this->size.x + x,
                        z,
                        this->position.y * this->size.y + y,
                    };

                    Block block(block_pos, this->all_blocks[i]);
                    block.draw_to(window, camera_view, &this->all_drawable_faces[i]);
                    i++;
                }
            }
        }
    }

    glm::vec2 Chunck::get_position(){
        return this->position;
    }

    BlockType Chunck::get_block(glm::vec3 position){
        return this->all_blocks[get_index(position, this->size)];
    }
};