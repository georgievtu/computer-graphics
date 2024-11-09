#version 460 core

in vec2 v_tex_coord;

uniform sampler2D tex;

out vec4 o_color;

void main()
{
    o_color = texture(tex, v_tex_coord);
}

