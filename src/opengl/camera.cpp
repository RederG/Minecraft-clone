#include "../../headers/opengl/camera.hpp"

namespace gl{
    void camera_update_pitch_yaw(GLFWwindow* window, double mouse_x, double mouse_y);
    void camera_update_wheel(GLFWwindow* window, double wheel_x, double wheel_y);

    Camera* current_camera = nullptr;

    Camera::Camera(){
        this->mouse_change_state = true;
        current_camera = this;
        camera_update_pitch_yaw(nullptr, 0, 0);
        current_camera = nullptr;
    }

    Camera::Camera(float field_of_view, float ratio, float near, float far)
    : max_fov(field_of_view), fov(field_of_view), aspect_ratio(ratio), near_plane(near), far_plane(far){
        this->time_usable = std::chrono::high_resolution_clock::now();
        this->usable = false;
        this->mouse_change_state = true;
        current_camera = this;
        camera_update_pitch_yaw(nullptr, 0, 0);
        current_camera = nullptr;
    }

    void Camera::create(float field_of_view, float ratio, float near, float far){
        this->max_fov = this->fov = field_of_view;
        this->aspect_ratio = ratio;
        this->near_plane = near;
        this->far_plane = far;
        this->time_usable = std::chrono::high_resolution_clock::now();
        this->usable = false;
        this->mouse_change_state = true;
        current_camera = this;
        camera_update_pitch_yaw(nullptr, 0, 0);
        current_camera = nullptr;
    }

    void Camera::update(GLFWwindow* window, float aspect_ratio){
        this->aspect_ratio = aspect_ratio;
        
        if(this->check_position)
            this->update_position(window);

        current_camera = this;
        if(this->usable){
            if(this->check_mouse_movement)
                glfwSetCursorPosCallback(window, camera_update_pitch_yaw);
            if(this->check_mouse_wheel)
                glfwSetScrollCallback(window, camera_update_wheel);
        }
        else{
            glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y){});
            glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y){});
        }
    }

    bool Camera::is_checking_mouse_movement(){
        return this->check_mouse_movement;
    }

    bool Camera::is_checking_mouse_wheel(){
        return this->check_mouse_wheel;
    }

    bool Camera::is_checking_position(){
        return this->check_position;
    }

    void Camera::set_checking_mouse_movement(bool state){
        this->check_mouse_movement = state;
        this->mouse_change_state = true;
    }

    void Camera::set_checking_mouse_wheel(bool state){
        this->check_mouse_wheel = state;
    }

    void Camera::set_checking_position(bool state){
        this->check_position = state;
    }

    glm::mat4 Camera::get_view(){
        glm::mat4 view = glm::lookAt(this->position, this->target, this->world_up);
        glm::mat4 perspective = glm::perspective(glm::radians(this->fov), this->aspect_ratio, this->near_plane, this->far_plane);
        return perspective * view;
    }

    glm::vec3 Camera::get_position(){
        return this->position;
    }

    void Camera::update_position(GLFWwindow* window){
        if(this->usable){
            float camera_speed = 0.8f;
            glm::vec3 camera_left = glm::normalize(glm::cross(this->front, this->world_up));
            glm::vec3 world_front = glm::normalize(glm::cross(camera_left, this->world_up));

            if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                camera_speed *= 5;

            // UP
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        
                this->position.y += camera_speed * Tool::delta_time;
            // DOWN
            if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)   
                this->position.y -= camera_speed * Tool::delta_time;

            // FRONT
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            
                this->position -= world_front * camera_speed * Tool::delta_time;
            // BACK
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            
                this->position += world_front * camera_speed * Tool::delta_time;
            // LEFT
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            
                this->position -= camera_left * camera_speed * Tool::delta_time;
            // RIGHT
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            
                this->position += camera_left * camera_speed * Tool::delta_time;
        }
        this->target = this->front + this->position;
        world_up = {0.0f, 1.0f, 0.0f};

        float time_offset = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - this->time_usable).count();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && time_offset > 0.2f && !this->usable){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            this->usable = true;
            this->time_usable = std::chrono::high_resolution_clock::now();
            this->mouse_change_state = true;
        }
        else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && time_offset > 0.2f && this->usable){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            this->usable = false;
            this->time_usable = std::chrono::high_resolution_clock::now();
        }
    }

    void camera_update_pitch_yaw(GLFWwindow* window, double mouse_x, double mouse_y){
        if(current_camera->mouse_change_state)
            current_camera->previous_mouse_pos = {mouse_x, mouse_y};
        current_camera->mouse_change_state = false;

        current_camera->sensitivity = 0.1f;
        glm::vec2 mouse_offset = {
            (mouse_x - current_camera->previous_mouse_pos.x) * current_camera->sensitivity,
            (current_camera->previous_mouse_pos.y - mouse_y) * current_camera->sensitivity
        };
        current_camera->previous_mouse_pos = {mouse_x, mouse_y};

        current_camera->yaw += mouse_offset.x;
        current_camera->pitch += mouse_offset.y;

        current_camera->pitch = (current_camera->pitch >  89.0f) ?  89.0 : current_camera->pitch;
        current_camera->pitch = (current_camera->pitch < -89.0f) ? -89.0 : current_camera->pitch;

        current_camera->front = {
            cos(glm::radians(current_camera->yaw)) * cos(glm::radians(current_camera->pitch)),
            sin(glm::radians(current_camera->pitch)),
            sin(glm::radians(current_camera->yaw)) * cos(glm::radians(current_camera->pitch))
        };
        current_camera->front = glm::normalize(current_camera->front);
    }

    void camera_update_wheel(GLFWwindow* window, double wheel_x, double wheel_y){
        current_camera->fov -= wheel_y;
        current_camera->fov = (current_camera->fov > current_camera->max_fov) ? current_camera->max_fov : current_camera->fov;
        current_camera->fov = (current_camera->fov < 00.0f) ? 00.0f : current_camera->fov;
    }
};