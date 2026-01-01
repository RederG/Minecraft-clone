#version 330 core

in vec4 block_color;
in vec2 block_texture_coords;

out vec4 fragment;
uniform sampler2D block_texture;

void main(){
    fragment = texture(block_texture, block_texture_coords) * block_color;
}