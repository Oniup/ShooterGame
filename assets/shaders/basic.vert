#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_uv;
layout (location = 3) in vec3 a_normals;
layout (location = 4) in float a_texture_id;

void main() {
    gl_Position = vec4(a_position.xyz, 1.0);
}