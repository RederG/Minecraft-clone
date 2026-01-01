#ifndef __BUFFERS_HPP__
    #define __BUFFERS_HPP__

    #include "../opengl/opengl.hpp"

    namespace Minecraft{
        extern gl::Buffer::VertexLayout Block_buffer_layout;
        extern gl::Buffer::VertexArray Block_front_vertex_array;
        extern gl::Buffer::VertexArray Block_back_vertex_array;
        extern gl::Buffer::VertexArray Block_right_vertex_array;
        extern gl::Buffer::VertexArray Block_left_vertex_array;
        extern gl::Buffer::VertexArray Block_up_vertex_array;
        extern gl::Buffer::VertexArray Block_down_vertex_array;

        void init_buffers();
        void terminate_buffers();
    };

#endif