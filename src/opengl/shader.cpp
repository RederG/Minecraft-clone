#include "../../headers/opengl/shader.hpp"
#include "../../headers/opengl/base.hpp"

namespace gl{
    ShaderProgram::ShaderProgram(){}

    ShaderProgram::~ShaderProgram(){
        Tool_verify(glDeleteProgram(this->id));
        this->all_sources_code.clear();
        this->all_uniforms_location.clear();
    }

    ShaderProgram::ShaderProgram(std::string file, ShaderType type){
        this->id = glCreateProgram();
        this->is_created = true;
        this->link_with(file, type);
    }

    void ShaderProgram::create(){
        if(!this->is_created){
            this->is_created = true;
            this->id = glCreateProgram();
        }
        else
            Tool::throw_opengl_error("The shader is already created !!", "gl::ShaderProgram::create()");
    }

    void ShaderProgram::link_with(std::string file, ShaderType type){
        if(!this->is_created)
            Tool::throw_opengl_error("The shader is not already created !!", "void gl::ShaderProgram::link_with(std::string file, ShaderType type)");
        unsigned int gl_shader_type;
        (type == ShaderType::Vertex) ? gl_shader_type = GL_VERTEX_SHADER : gl_shader_type = GL_FRAGMENT_SHADER;
        this->all_sources_code[gl_shader_type] = get_shader_source_code_of(file);

        unsigned int shader_id;
        Tool_verify(shader_id = glCreateShader(gl_shader_type));

        const char* src = this->all_sources_code[gl_shader_type].c_str();
        Tool_verify(glShaderSource(
            shader_id, 
            1,
            &src, 
            0
        ));

        Tool_verify(glCompileShader(shader_id));

        int compile_status;
        Tool_verify(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status));
        if(compile_status == GL_FALSE){
            int length;
            Tool_verify(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
            char* log = new char[length];
            Tool_verify(glGetShaderInfoLog(shader_id, length, &length, log));
            std::string shader_type = (gl_shader_type == GL_VERTEX_SHADER) ? "Vertex shader) :\n" : "Fragment shader) :\n";
            Tool::throw_error("OpenGL's shader compilation error (" + shader_type + log);
        }
        
        glAttachShader(this->id, shader_id);
        glLinkProgram(this->id);
        glDeleteShader(shader_id);
    }

    void ShaderProgram::validate(){
        if(!this->is_created)
            Tool::throw_opengl_error("The shader is not already created !!", "void gl::ShaderProgram::validate()");
        Tool_verify(glValidateProgram(this->id));
    }

    void ShaderProgram::use_me() const{
        if(!this->is_created)
            Tool::throw_opengl_error("The shader is not already created !!", "void gl::ShaderProgram::use_me()");
        Tool_verify(glUseProgram(this->id));
    }

    void ShaderProgram::forget_me() const{
        if(!this->is_created)
            Tool::throw_opengl_error("The shader is not already created !!", "void gl::ShaderProgram::forget_me()");
        Tool_verify(glUseProgram(0));
    }

    void ShaderProgram::set_uniform(int values_number, std::string name, float v0, float v1, float v2, float v3){
        if(gl::auto_binding())
            this->use_me();
        if(values_number == 1)
            Tool_verify(glUniform1f(this->get_uniform_location(name), v0));
        if(values_number == 2)
            Tool_verify(glUniform2f(this->get_uniform_location(name), v0, v1));
        if(values_number == 3)
            Tool_verify(glUniform3f(this->get_uniform_location(name), v0, v1, v2));
        if(values_number == 4)
            Tool_verify(glUniform4f(this->get_uniform_location(name), v0, v1, v2, v3));
        if(gl::auto_binding())
            this->forget_me();
    }

    void ShaderProgram::set_uniform(int values_number, std::string name, int v0, int v1, int v2, int v3){
        if(gl::auto_binding())
            this->use_me();
        if(values_number == 1)
            Tool_verify(glUniform1i(this->get_uniform_location(name), v0));
        if(values_number == 2)
            Tool_verify(glUniform2i(this->get_uniform_location(name), v0, v1));
        if(values_number == 3)
            Tool_verify(glUniform3i(this->get_uniform_location(name), v0, v1, v2));
        if(values_number == 4)
            Tool_verify(glUniform4i(this->get_uniform_location(name), v0, v1, v2, v3));
        if(gl::auto_binding())
            this->forget_me();
    }

    void ShaderProgram::set_uniform(int values_number, std::string name, bool v0, bool v1, bool v2, bool v3){
        this->set_uniform(values_number, name, int(v0), int(v1), int(v2), int(v3));
    }

    void ShaderProgram::set_uniform(int values_number, std::string name, unsigned int  v0, unsigned int  v1, unsigned int  v2, unsigned int  v3){
        if(gl::auto_binding())
            this->use_me();
        if(values_number == 1)
            Tool_verify(glUniform1ui(this->get_uniform_location(name), v0));
        if(values_number == 2)
            Tool_verify(glUniform2ui(this->get_uniform_location(name), v0, v1));
        if(values_number == 3)
            Tool_verify(glUniform3ui(this->get_uniform_location(name), v0, v1, v2));
        if(values_number == 4)
            Tool_verify(glUniform4ui(this->get_uniform_location(name), v0, v1, v2, v3));
        if(gl::auto_binding())
            this->forget_me();
    }

    void ShaderProgram::set_uniform(int values_number, std::string name, double v0, double v1, double v2, double v3){
        if(gl::auto_binding())
            this->use_me();
        if(values_number == 1)
            Tool_verify(glUniform1d(this->get_uniform_location(name), v0));
        if(values_number == 2)
            Tool_verify(glUniform2d(this->get_uniform_location(name), v0, v1));
        if(values_number == 3)
            Tool_verify(glUniform3d(this->get_uniform_location(name), v0, v1, v2));
        if(values_number == 4)
            Tool_verify(glUniform4d(this->get_uniform_location(name), v0, v1, v2, v3));
        if(gl::auto_binding())
            this->forget_me();
    }

    void ShaderProgram::set_uniform_matrix4f(std::string name, glm::mat4* matrix, bool transpose){
        if(auto_binding())
            this->use_me();
        unsigned int Trans = (transpose == true) ? GL_TRUE : GL_FALSE;
        glUniformMatrix4fv(this->get_uniform_location(name), 1, Trans, glm::value_ptr(*matrix));
        if(auto_binding())
            this->forget_me();
    }

    int ShaderProgram::get_uniform_location(std::string name){
        if(!this->is_created)
            Tool::throw_opengl_error("The shader is not already created !!", "void gl::ShaderProgram::get_uniform_location(std::string name)");
        if(this->all_uniforms_location.find(name) != this->all_uniforms_location.end())
            return this->all_uniforms_location[name];
        int location;
        Tool_verify(location = glGetUniformLocation(this->id, name.c_str()));
        this->all_uniforms_location[name] = location;
        if(location == -1)
            Tool::log("Warning : uniform \"" + name + "\" not found. (GLSL)");
        return location;
    }

    std::string get_shader_source_code_of(std::string file_path){
        if(!std::filesystem::exists(file_path))
            Tool::throw_error("Shader's source code doesn't exist.\n=> Path : " + file_path);
        std::string source_code;
        std::fstream file(file_path, std::ios::in);
        if(file.is_open()){
            while (!file.eof()){
                std::string line;
                std::getline(file, line);
                source_code.append(line + "\n");
            }
            file.close();
        }
        return source_code;
    }
}