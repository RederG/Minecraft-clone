#ifndef __SHADER__
    #define __SHADER__

    #include "../tool.hpp"
    #include "base.hpp"

    namespace gl{
        enum ShaderType{
            Vertex, Fragment
        };

        class ShaderProgram{
            public:
                ShaderProgram();
                ShaderProgram(std::string file, ShaderType type);
                ~ShaderProgram();
                void create();
                void link_with(std::string file, ShaderType type);
                void validate();
                void use_me() const;
                void forget_me() const;
                void set_uniform(int values_number, std::string name, float v0, float v1 = 0.0f, float v2 = 0.0f, float v3 = 0.0f);
                void set_uniform(int values_number, std::string name, int v0, int v1 = 0.0f, int v2 = 0.0f, int v3 = 0.0f);
                void set_uniform(int values_number, std::string name, bool v0, bool v1 = false, bool v2 = false, bool v3 = false);
                void set_uniform(int values_number, std::string name, unsigned int v0, unsigned int v1 = 0.0f, unsigned int v2 = 0.0f, unsigned int v3 = 0.0f);
                void set_uniform(int values_number, std::string name, double v0, double v1 = 0.0f, double v2 = 0.0f, double v3 = 0.0f);
                void set_uniform_matrix4f(std::string name, glm::mat4* matrix, bool transpose);
                int get_uniform_location(std::string name);
            private:
                unsigned int id;
                bool is_created = false;
                std::map<unsigned int, std::string> all_sources_code;
                std::map<std::string, int> all_uniforms_location;
        };

        std::string get_shader_source_code_of(std::string file);
    };

#endif