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

                    BlockType left = world->get_block({block_pos.x - 1, block_pos.y, block_pos.z});
                    BlockType right = world->get_block({block_pos.x + 1, block_pos.y, block_pos.z});
                    BlockType down = world->get_block({block_pos.x, block_pos.y - 1, block_pos.z});
                    BlockType up = world->get_block({block_pos.x, block_pos.y + 1, block_pos.z});
                    BlockType back = world->get_block({block_pos.x, block_pos.y, block_pos.z - 1});
                    BlockType front = world->get_block({block_pos.x, block_pos.y, block_pos.z + 1});

                    if(left !=  BlockType::Air  &&      left !=     BlockType::Nothing)
                        this->all_drawable_faces[i].left = false;
                    if(right != BlockType::Air  &&      right !=    BlockType::Nothing)
                        this->all_drawable_faces[i].right = false;
                    if(down !=  BlockType::Air  &&      down !=     BlockType::Nothing)
                        this->all_drawable_faces[i].down = false;
                    if(up !=    BlockType::Air  &&      up !=       BlockType::Nothing)
                        this->all_drawable_faces[i].up = false;
                    if(back !=  BlockType::Air  &&      back !=     BlockType::Nothing)
                        this->all_drawable_faces[i].back = false;
                    if(front != BlockType::Air  &&      front !=    BlockType::Nothing)
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

    bool Chunck::is_mine(glm::vec3 position){
        glm::vec3 start_pos = {
            this->position.x * this->size.x,
            this->size.z,
            this->position.y * this->size.y
        };

        glm::vec3 end_pos = {
            this->position.x * this->size.x + this->size.x,
            0,
            this->position.y * this->size.y + this->size.y
        };

        if(position.x >= start_pos.x && position.x < end_pos.x &&
            position.y < start_pos.y && position.y >= end_pos.y &&
            position.z >= start_pos.z && position.z < end_pos.z)
            return true;
        return false;
    }

    glm::vec2 Chunck::get_position(){
        return this->position;
    }

    BlockType Chunck::get_block(glm::vec3 position){
        if(this->is_mine(position))
            return this->all_blocks[get_index(position, this->size)];
        return BlockType::Nothing;
    }
};