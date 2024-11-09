#version 460 core

layout(location = 0) in vec3 i_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    vec4 pos = u_projection * u_view * u_model * vec4(i_pos, 1.0f);

    gl_Position = pos;
}

