#version 460 core

layout(location = 0) in vec3 i_pos;

uniform mat4 u_pvm;

void main()
{
    vec4 pos = vec4(i_pos, 1.0f);
    pos *= u_pvm;
    gl_Position = pos;
}

