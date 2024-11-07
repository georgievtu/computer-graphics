#version 460 core

layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec2 i_tex_coord;

uniform mat4 u_pvm;

void main()
{
    vec4 pos = vec4(i_pos, 1.0f);
    pos *= u_pvm;
    gl_Position = pos;
}

