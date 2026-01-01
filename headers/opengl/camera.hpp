#ifndef __CAMERA_HPP__
    #define __CAMERA_HPP__

    #include "base.hpp"
    #include "../tool.hpp"

    namespace gl{
        class Camera{
            public:
                Camera();
                Camera(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
                void create(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
                void update(GLFWwindow* window, float aspect_ratio);
                bool is_checking_mouse_wheel();
                bool is_checking_mouse_movement();
                bool is_checking_position();
                void set_checking_mouse_wheel(bool state);
                void set_checking_mouse_movement(bool state);
                void set_checking_position(bool state);
                friend void camera_update_pitch_yaw(GLFWwindow* window, double mouse_x, double mouse_y);
                friend void camera_update_wheel(GLFWwindow* window, double wheel_x, double wheel_y);
                glm::mat4 get_view();
                glm::vec3 get_position();
            private:
                float max_fov, fov, aspect_ratio, near_plane, far_plane, pitch, yaw, sensitivity;
                bool check_mouse_wheel = true, check_mouse_movement = true, check_position = true, mouse_change_state = true, usable = true;
                glm::vec3 position, target, world_up, front;
                glm::vec2 previous_mouse_pos;
                std::chrono::_V2::system_clock::time_point time_usable;

                void update_position(GLFWwindow* window);
        };
    };

#endif