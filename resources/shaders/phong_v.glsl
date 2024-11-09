#version 460 core

layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec2 i_tex_coord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_tex_coord;
out vec3 v_pos;
out vec3 v_normal;

void main()
{
    v_pos = vec3(u_model * vec4(i_pos, 1.0f));
    v_normal = mat3(transpose(inverse(u_model))) * i_normal;

    gl_Position = u_projection * u_view * vec4(v_pos, 1.0f);

    v_tex_coord = i_tex_coord;
}

