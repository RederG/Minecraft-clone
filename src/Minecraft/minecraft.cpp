#include "../../headers/Minecraft/minecraft.hpp"
#include "../../headers/Minecraft/buffers.hpp"
#include "../../headers/Minecraft/shaders.hpp"
#include "../../headers/Minecraft/textures.hpp"
#include "../../headers/Minecraft/chunck.hpp"
#include "../../headers/Minecraft/world.hpp"

const std::string MINECRAFT_APP_TIMER = "minecraft_app_timer";
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if(!glfwInit())
            Tool::throw_error("GLFW not initiaized");
        else
            Tool::glfw_initialized = true;

        window = glfwCreateWindow(window_size.x, window_size.y, "Minecraft", nullptr, nullptr);

        if(!window)
            Tool::throw_error("Window not created");

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
            Tool::throw_error("GLAD not initialized");
        else
            Tool::glad_initialized = true;

        Tool::update_delta_time();
        glViewport(0, 0, window_size.x, window_size.y);
        gl::set(gl::Options::Depth_testing, true);

        init_buffers();
        init_shaders();
        init_textures();

        Tool::log("All Minecraft's data loaded\n\tWe are ready to play");
    }

    void terminate(){
        terminate_shaders();
        terminate_textures();
        terminate_buffers();

        glfwTerminate();

        Tool::Timer::stop(MINECRAFT_APP_TIMER);
        float duration = Tool::Timer::get_duration(MINECRAFT_APP_TIMER);
        float average_fps = Tool::get_average_fps();
        Tool::log("Application ended\n\tActivity time : " + std::to_string(duration) + " seconds");
        std::cout << "\nAverage FPS : " << average_fps << "\n" << std::endl;
    }

    void play(){
        if(Tool::glad_initialized && Tool::glfw_initialized){
            World world(1, {8, 8, 255});
            gl::Camera camera(45.0f, float(window_size.x / window_size.y), 0.1f, 100.0f);
            
            world.update({2.0f, 2.0f, 10.0f});

            while(!glfwWindowShouldClose(window)){
                glfwSetFramebufferSizeCallback(window, update_window_size);

                gl::Renderer::clear(gl::Color(0.25f, 0.25f, 1.0f, 1.0f));

                if(!is_minimized){
                    camera.update(window, float(window_size.x / window_size.y));
                    world.draw_to(window, camera.get_view());
                }

                glfwPollEvents();
                glfwSwapBuffers(window);

                Tool::update_delta_time();

                std::string title = "Minecraft, FPS : " + std::to_string(1 / Tool::delta_time);
                glfwSetWindowTitle(window, title.c_str());
            }
        }
        else
            Tool::throw_error("You want to play but GLAD and/or GLFW are unloaded, poor of you ;)");
    }
};