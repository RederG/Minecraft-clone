#include "../../headers/Minecraft/player.hpp"

namespace Minecraft{
    Player::Player(std::string name){
        this->name = name;
        this->position = {0, 0, 0};
        this->camera.create(45.0f, 1, 0.1f, 100.0f);
        this->id = generate_entity_id();
        add_entity(this);
    }

    void Player::update(GLFWwindow* window){
        int window_x, window_y;
        glfwGetWindowSize(window, &window_x, &window_y);
        
        float aspect_ratio = window_x;
        aspect_ratio /= window_y;
        this->camera.update(window, aspect_ratio);
    }

    gl::Camera* Player::get_camera(){
        return &this->camera;
    }
};