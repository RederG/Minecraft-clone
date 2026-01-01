#include "../../headers/Minecraft/block.hpp"
#include "../../headers/Minecraft/textures.hpp"

namespace Minecraft{
    Block::Block(){
        this->position = {0.0f, 0.0f, 0.0f};
    }

    Block::Block(glm::vec3 position, BlockType type){
        this->position = position;
        this->type = type;
    }

    void Block::draw_to(GLFWwindow* window, glm::mat4* camera_view, BlockDrawableFace* drawable_faces){
        if(this->type != BlockType::Air){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::translate(model, this->position);

            glm::mat4 trans = (*camera_view) * model;
            Block_shader.set_uniform_matrix4f("transform", &trans, false);

            if(drawable_faces->front)
                gl::Renderer::draw(&Block_front_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
            if(drawable_faces->back)
                gl::Renderer::draw(&Block_back_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
            if(drawable_faces->left)
                gl::Renderer::draw(&Block_left_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
            if(drawable_faces->right)
                gl::Renderer::draw(&Block_right_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
            if(drawable_faces->up)
                gl::Renderer::draw(&Block_up_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
            if(drawable_faces->down)
                gl::Renderer::draw(&Block_down_vertex_array, nullptr, get_texture_of(this->type), &Block_shader);
        }
    }
};