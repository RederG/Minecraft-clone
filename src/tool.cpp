#include "../headers/tool.hpp"

const std::string MINECRAFT_LOG_FILE_NAME = "MinecraftApp.log";

const std::map<unsigned int, std::string> opengl_error{
    {GL_INVALID_ENUM,                   "Invalid enum"},
    {GL_INVALID_VALUE,                  "Invalid value"},
    {GL_INVALID_OPERATION,              "Invalid operation"},
    {GL_INVALID_FRAMEBUFFER_OPERATION,  "Invalid framebuffer operation"},
    {GL_OUT_OF_MEMORY,                  "Out of memory"},
};

namespace Tool{
    auto previous_time = std::chrono::high_resolution_clock::now();
    float delta_time = 0.0f;
    std::fstream log_file;
    std::vector<float> all_delta_times;

    bool glfw_initialized = false;
    bool glad_initialized = false;

    void update_delta_time(){
        delta_time = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - previous_time).count();
        previous_time = std::chrono::high_resolution_clock::now();
        all_delta_times.push_back(delta_time);
        if(all_delta_times.size() > 100){
            float average_dt = 1 / get_average_fps();
            all_delta_times.clear();
            all_delta_times.push_back(average_dt);
        }
    }

    void throw_error(std::string message){
        log("[ERROR] : " + message);
        __debugbreak();
        exit(EXIT_FAILURE);
    }

    void throw_opengl_error(std::string error, std::string opengl_function){
        log("[OpenGL ERROR] : " + error + "\n\t=> Function : " + opengl_function + "\n\n");
        __debugbreak();
        exit(EXIT_FAILURE);
    }

    void verify_gl_errors(std::string opengl_function){
        unsigned int current_error = glGetError();
        if(current_error != GL_NO_ERROR){
            std::string error = opengl_error.at(current_error);
            throw_opengl_error(error, opengl_function);
        }
    }

    void log(std::string message){
        log(message, MINECRAFT_LOG_FILE_NAME);
    }

    void log(std::string message, std::string file_path){
        if(!std::filesystem::exists(file_path)){
            log_file.open(file_path, std::ios::out);
            log_file.close();
        }
        log_file.open(file_path, std::ios::app);
        if(log_file.is_open()){
            auto now = std::chrono::high_resolution_clock::now();
            auto today = std::format("{:%d/%m/%Y}", now);
            auto time = std::format("{:%H:%M:%S}", now);
            log_file << "[Today = " << today << ", now = " << time << "]\n\t" << message << "\n\n";
            log_file.close();
        }
    }

    void log_clear(){
        log_clear(MINECRAFT_LOG_FILE_NAME);
    }

    void log_clear(std::string file_path){
        log_file.open(file_path, std::ios::out);
        log_file << "";
        log_file.close();
    }

    float get_average_fps(){
        float big_delta_time = 0;
        for(float dt : all_delta_times)
            big_delta_time += dt;
        float average = big_delta_time / all_delta_times.size();
        return 1 / average;
    }

    namespace Timer{
        std::map<std::string, std::chrono::_V2::system_clock::time_point> all_begins;
        std::map<std::string, float> all_durations;
        std::map<std::string, State> all_states;

        void create(std::string name){
            if(!exists(name)){
                all_begins[name] = std::chrono::high_resolution_clock::now();
                all_durations[name] = 0.0f;
                all_states[name] = State::Inactive;
            }
            else
                throw_error("The timer \"" + name + "\" already exists");
        }

        bool exists(std::string name){
            if(all_begins.find(name) != all_begins.end())
                return true;
            return false;
        }

        void start(std::string name){
            if(exists(name)){
                State timer_state = all_states[name];
                if(timer_state == State::Inactive || timer_state == State::Stopped){
                    all_begins[name] = std::chrono::high_resolution_clock::now();
                    all_durations[name] = 0.0f;
                    all_states[name] = State::Counting;
                }
                else if(timer_state == State::Counting)
                    throw_error("The timer \"" + name + "\" is already counting");
            }
            else
                throw_error("The timer \"" + name + "\" doesn't exists");
        }

        void stop(std::string name){
            if(exists(name)){
                State timer_state = all_states[name];
                if(timer_state == State::Counting){
                    auto now = std::chrono::high_resolution_clock::now();
                    all_durations[name] = std::chrono::duration<float>(now - all_begins[name]).count();
                    all_begins[name] = now;
                    all_states[name] = State::Stopped;
                }
                else if(timer_state == State::Stopped)
                    throw_error("The timer \"" + name + "\" is already stopped");
                else
                    throw_error("The timer \"" + name + "\" is inactive");
            }
            else
                throw_error("The timer \"" + name + "\" doesn't exists");
        }

        float get_duration(std::string name){
            if(exists(name)){
                State timer_state = all_states[name];
                if(timer_state == State::Counting){
                    auto now = std::chrono::high_resolution_clock::now();
                    all_durations[name] = std::chrono::duration<float>(now - all_begins[name]).count();
                    return all_durations[name];
                }
                else if(timer_state == State::Stopped)
                    return all_durations[name];
                else{
                    throw_error("The timer \"" + name + "\" is inactive");
                    return 0.0f;
                }
            }
            else{
                throw_error("The timer \"" + name + "\" doesn't exists");
                return 0.0f;
            }
        }

        State get_state(std::string name){
            if(exists(name))
                return all_states[name];
            throw_error("The timer \"" + name + "\" doesn't exists");
            return State::Stopped;
        }
    };
};