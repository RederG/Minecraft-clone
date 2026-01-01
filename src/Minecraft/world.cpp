#include "../../headers/Minecraft/world.hpp"
#include "../../headers/Minecraft/chunck.hpp"

namespace Minecraft{
    World::World(int r_distance, glm::vec3 c_size)
    : render_distance(r_distance), chunck_size(c_size){}

    void World::draw_to(GLFWwindow* window, glm::mat4 camera_view){
        for(int i = 0; i < this->all_current_chuncks.size(); i++)
            this->all_current_chuncks[i]->draw_to(window, &camera_view, this);
    }

    void World::update(glm::vec3 position){
        this->all_current_chuncks.clear();

        glm::vec3 chunck_center = {position.x, position.y, 0};
        for(int y = chunck_center.y - this->render_distance; y <= chunck_center.y + this->render_distance; y++){
            for(int x = chunck_center.x - this->render_distance; x <= chunck_center.x + this->render_distance; x++){
                glm::vec2 chunck_pos = {x, y};
                this->all_current_chuncks.push_back(new Chunck(chunck_pos, this->chunck_size));
            }
        }
        for(auto& chunck : this->all_current_chuncks)
            chunck->update(this);
    }

    BlockType World::get_block(glm::vec3 position){
        int x = int(position.x / this->chunck_size.x);
        int y = int(position.z / this->chunck_size.y);

        Chunck* chunck_target = nullptr;
        for(int i = 0; i < this->all_current_chuncks.size(); i++){
            Chunck* current_chunck = this->all_current_chuncks[i];
            if(current_chunck->get_position() == glm::vec2({x, y})){
                chunck_target = current_chunck;
                break;
            }
        }

        if(chunck_target != nullptr)
            return chunck_target->get_block(position);
        return BlockType::Air;
    }
};