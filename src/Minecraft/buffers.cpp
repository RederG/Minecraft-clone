#include "../../headers/Minecraft/buffers.hpp"

namespace Minecraft{
    gl::Buffer::Vertex Block_front_buffer;
    gl::Buffer::Vertex Block_back_buffer;
    gl::Buffer::Vertex Block_right_buffer;
    gl::Buffer::Vertex Block_left_buffer;
    gl::Buffer::Vertex Block_up_buffer;
    gl::Buffer::Vertex Block_down_buffer;
    gl::Buffer::VertexLayout Block_buffer_layout;
    gl::Buffer::VertexArray Block_front_vertex_array;
    gl::Buffer::VertexArray Block_back_vertex_array;
    gl::Buffer::VertexArray Block_right_vertex_array;
    gl::Buffer::VertexArray Block_left_vertex_array;
    gl::Buffer::VertexArray Block_up_vertex_array;
    gl::Buffer::VertexArray Block_down_vertex_array;

    const float block_back_buffer_data[] = {
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     0.00f,
         0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
         0.5f,    0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
         0.5f,    0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
        -0.5f,    0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     0.00f,
    };

    const float block_front_buffer_data[] = {
        -0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
         0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     0.00f,
         0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
         0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
        -0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
        -0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
    };

    const float block_left_buffer_data[] = {
        -0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
        -0.5f,    0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
        -0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     0.00f,
        -0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
    };

    const float block_right_buffer_data[] = {
         0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
         0.5f,    0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
         0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
         0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
         0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     0.00f,
         0.5f,    0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.50f,     1.00f,
    };

    const float block_down_buffer_data[] = {
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.75f,     0.00f,
         0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          1.00f,     0.00f,
         0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          1.00f,     1.00f,
         0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          1.00f,     1.00f,
        -0.5f,   -0.5f,     0.5f,           1.0,    1.0,     1.0,     1.0,          0.75f,     1.00f,
        -0.5f,   -0.5f,    -0.5f,           1.0,    1.0,     1.0,     1.0,          0.75f,     0.00f,
    };

    const float block_up_buffer_data[] = {
        -0.5f,   0.5f,     -0.5f,           1.0,    1.0,     1.0,     1.0,          0.00f,     1.00f,
         0.5f,   0.5f,     -0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     1.00f,
         0.5f,   0.5f,      0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
         0.5f,   0.5f,      0.5f,           1.0,    1.0,     1.0,     1.0,          0.25f,     0.00f,
        -0.5f,   0.5f,      0.5f,           1.0,    1.0,     1.0,     1.0,          0.00f,     0.00f,
        -0.5f,   0.5f,     -0.5f,           1.0,    1.0,     1.0,     1.0,          0.00f,     1.00f
    };

    void init_buffers(){
        // Initializing the layout of all block buffers
        Block_buffer_layout.add(3, gl::Type::Float, false, gl::Buffer::VertexType::Position);
        Block_buffer_layout.add(4, gl::Type::Float, false, gl::Buffer::VertexType::Color);
        Block_buffer_layout.add(2, gl::Type::Float, false, gl::Buffer::VertexType::TextureCoords);

        // Initializing all buffers
        Block_front_buffer.create();
        Block_front_buffer.set_data(block_front_buffer_data, sizeof(block_front_buffer_data));

        Block_back_buffer.create();
        Block_back_buffer.set_data(block_back_buffer_data, sizeof(block_back_buffer_data));

        Block_left_buffer.create();
        Block_left_buffer.set_data(block_left_buffer_data, sizeof(block_left_buffer_data));

        Block_right_buffer.create();
        Block_right_buffer.set_data(block_right_buffer_data, sizeof(block_right_buffer_data));

        Block_up_buffer.create();
        Block_up_buffer.set_data(block_up_buffer_data, sizeof(block_up_buffer_data));

        Block_down_buffer.create();
        Block_down_buffer.set_data(block_down_buffer_data, sizeof(block_down_buffer_data));

        // Initializing all vertex arrays
        Block_front_vertex_array.create();
        Block_front_vertex_array.configure_with(&Block_front_buffer, &Block_buffer_layout);

        Block_back_vertex_array.create();
        Block_back_vertex_array.configure_with(&Block_back_buffer, &Block_buffer_layout);

        Block_left_vertex_array.create();
        Block_left_vertex_array.configure_with(&Block_left_buffer, &Block_buffer_layout);

        Block_right_vertex_array.create();
        Block_right_vertex_array.configure_with(&Block_right_buffer, &Block_buffer_layout);

        Block_up_vertex_array.create();
        Block_up_vertex_array.configure_with(&Block_up_buffer, &Block_buffer_layout);

        Block_down_vertex_array.create();
        Block_down_vertex_array.configure_with(&Block_down_buffer, &Block_buffer_layout);

        Tool::log("Minecraft's buffers initiated");
    }

    void terminate_buffers(){
        Block_front_buffer.~Vertex();
        Block_front_vertex_array.~VertexArray();

        Block_back_buffer.~Vertex();
        Block_back_vertex_array.~VertexArray();

        Block_left_buffer.~Vertex();
        Block_left_vertex_array.~VertexArray();

        Block_right_buffer.~Vertex();
        Block_right_vertex_array.~VertexArray();

        Block_up_buffer.~Vertex();
        Block_up_vertex_array.~VertexArray();

        Block_down_buffer.~Vertex();
        Block_down_vertex_array.~VertexArray();

        Tool::log("Minecraft's buffers terminated");
    }
};