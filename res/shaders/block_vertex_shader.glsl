#version 330 core

layout(location = 0) in vec3 m_position;
layout(location = 1) in vec4 m_color;
layout(location = 2) in vec2 m_texture_coords;

out vec4 block_color;
out vec2 block_texture_coords;

uniform mat4 transform;

void main(){
    gl_Position = transform * vec4(m_position, 1.0f);
    block_color = m_color;
    block_texture_coords = m_texture_coords;
}