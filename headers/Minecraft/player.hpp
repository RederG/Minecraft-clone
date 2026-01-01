#ifndef __PLAYER_HPP__
    #define __PLAYER_HPP__

    #include "entity.hpp"
    #include "../opengl/camera.hpp"

    namespace Minecraft{
        class Player : public Entity{
            public:
                Player(std::string name);
                void update(GLFWwindow* window) override;
                gl::Camera* get_camera();
            private:
                gl::Camera camera;
        };
    };

#endif