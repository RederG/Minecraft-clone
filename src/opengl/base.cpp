#include "../../headers/opengl/base.hpp"

namespace gl{
    bool auto_binding_state = true;

    bool auto_binding(){
        return auto_binding_state;
    }

    void auto_binding(bool state){
        auto_binding_state = state;
    }

    unsigned int get_size_of(unsigned int gl_type){
        switch (gl_type){
            case GL_INT:
                return sizeof(int);
            case GL_FLOAT:
                return sizeof(float);
            case GL_BOOL:
                return sizeof(bool);
            case GL_DOUBLE:
                return sizeof(double);
            case GL_UNSIGNED_INT:
                return sizeof(unsigned int);
            case GL_BYTE:
                return sizeof(char);
            case GL_UNSIGNED_BYTE:
                return sizeof(unsigned char);
            default:
                Tool::throw_opengl_error("Invalid enum", "gl::get_size_of(unsigned int gl_type)");
                return 0;
        }
    }

    void set(Options option, bool state){
        unsigned int func = functionalities.at(option);
        if(state == true)
            glEnable(func);
        else
            glDisable(func);
    }

    bool is_enabled(Options option){
        return glIsEnabled(functionalities.at(option));
    }
};