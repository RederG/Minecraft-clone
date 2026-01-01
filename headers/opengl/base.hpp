#ifndef __BASE__
    #define __BASE__

    #include "../tool.hpp"

    namespace gl{
        enum Type{
            Int, Float, Uint, Bool, Char, Uchar, Double
        };

        enum Options{
            Depth_testing
        };

        const std::map<Type, unsigned int> data_type{
            {Type::Bool,    GL_BOOL},
            {Type::Char,    GL_BYTE},
            {Type::Float,   GL_FLOAT},
            {Type::Int,     GL_INT},
            {Type::Uchar,   GL_UNSIGNED_BYTE},
            {Type::Uint,    GL_UNSIGNED_INT},
            {Type::Double,  GL_DOUBLE},
        };

        const std::map<Options, unsigned int> functionalities{
            {Options::Depth_testing, GL_DEPTH_TEST}
        };

        bool auto_binding();
        void auto_binding(bool state);
        unsigned int get_size_of(unsigned int gl_type);
        void set(Options option, bool state);
        bool is_enabled(Options option);

    };
#endif