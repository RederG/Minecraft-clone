#include "../../headers/Minecraft/minecraft.hpp"
#include "../../headers/Minecraft/buffers.hpp"
#include "../../headers/Minecraft/shaders.hpp"
#include "../../headers/Minecraft/textures.hpp"
#include "../../headers/Minecraft/chunck.hpp"
#include "../../headers/Minecraft/world.hpp"
#include "../../headers/Minecraft/entity.hpp"
#include "../../headers/Minecraft/player.hpp"

const std::string MINECRAFT_APP_TIMER = "minecraft_app_timer";
const std::string MINECRAFT_FPS_VIEWER_TIMER = "minecraft_fps_viewer_timer";
GLFWwindow* window = nullptr;
glm::vec2 window_size = {1080, 720};
bool is_minimized = false;

namespace Minecraft{

    void update_window_size(GLFWwindow* window, int window_x, int window_y){
        window_size = {window_x, window_y};
        glViewport(0, 0, window_x, window_y);
        is_minimized = (window_x <= 0 || window_y <= 0) ? true : false;
    }

    void init(){
        Tool::log_clear();
        Tool::log("Application lauched !!");

        Tool::Timer::create(MINECRAFT_APP_TIMER);
        Tool::Timer::start(MINECRAFT_APP_TIMER);

        Tool::Timer::create(MINECRAFT_FPS_VIEWER_TIMER);
        Tool::Timer::start(MINECRAFT_FPS_VIEWER_TIMER);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if(!glfwInit())
            Tool::throw_error("GLFW not initiaized");
        else
            Tool::glfw_initialized = true;

        window = glfwCreateWindow(window_size.x, window_size.y, "Minecraft, FPS : 0.0", nullptr, nullptr);

        if(!window)
            Tool::throw_error("Window not created");

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
            Tool::throw_error("GLAD not initialized");
        else
            Tool::glad_initialized = true;

        glfwSetFramebufferSizeCallback(window, update_window_size);

        Tool::update_delta_time();
        glViewport(0, 0, window_size.x, window_size.y);
        gl::set(gl::Options::Depth_testing, true);

        init_buffers();
        init_shaders();
        init_textures();
        init_entities();

        Tool::log("All Minecraft's data loaded\n\tWe are ready to play");
    }

    void terminate(){
        terminate_shaders();
        terminate_textures();
        terminate_buffers();
        terminate_entities();

        glfwTerminate();

        Tool::Timer::stop(MINECRAFT_APP_TIMER);
        Tool::Timer::stop(MINECRAFT_FPS_VIEWER_TIMER);
        float duration = Tool::Timer::get_duration(MINECRAFT_APP_TIMER);
        Tool::log("Application ended\n\tActivity time : " + std::to_string(duration) + " seconds");
    }

    void play(){
        if(Tool::glad_initialized && Tool::glfw_initialized){
            World world(1, {8, 8, 255});
            Player* player = new Player("Reder");

            world.update({2.0f, 2.0f, 10.0f});

            while(!glfwWindowShouldClose(window)){

                gl::Renderer::clear(gl::Color(0.25f, 0.25f, 1.0f, 1.0f));

                if(!is_minimized){
                    player->update(window);
                    world.draw_to(window, player->get_camera()->get_view());
                    
                    if(Tool::Timer::get_duration(MINECRAFT_FPS_VIEWER_TIMER) > 1.0f){
                        std::string title = "Minecraft, FPS : " + std::to_string(1 / Tool::delta_time);
                        glfwSetWindowTitle(window, title.c_str());
                        Tool::Timer::restart(MINECRAFT_FPS_VIEWER_TIMER);
                    }
                }

                glfwPollEvents();
                glfwSwapBuffers(window);

                Tool::update_delta_time();
            }
        }
        else
            Tool::throw_error("You want to play but GLAD and/or GLFW are unloaded, poor of you ;)");
    }
};