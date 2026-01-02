#ifndef __TOOL_HPP__
    #define __TOOL_HPP__

    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    #include <chrono>
    #include <map>
    #include <vector>
    #include <string>
    #include <filesystem>
    #include <fstream>
    #include <thread>
    #include <algorithm>

    #define Tool_verify(opengl_function){\
                while(glGetError() != GL_NO_ERROR);;\
                opengl_function;\
                Tool::verify_gl_errors(#opengl_function);\
            }

    namespace Tool{
        extern float delta_time;
        extern bool glfw_initialized;
        extern bool glad_initialized;

        void update_delta_time();
        void throw_error(std::string message);
        void throw_opengl_error(std::string error, std::string opengl_function);
        void verify_gl_errors(std::string opengl_function);
        void log(std::string message);
        void log(std::string message, std::string file_path);
        void log_clear();
        void log_clear(std::string file_path);
        float get_average_fps();

        namespace Timer{
            enum State{
                Counting, Stopped, Inactive
            };

            void create(std::string name);
            void start(std::string name);
            void stop(std::string name);
            void restart(std::string name);
            float get_duration(std::string name);
            State get_state(std::string name);
            bool exists(std::string name);
        };
    };

#endif