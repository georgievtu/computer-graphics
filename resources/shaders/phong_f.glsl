#version 460 core

in vec2 v_tex_coord;
in vec3 v_pos;
in vec3 v_normal;

uniform sampler2D tex;
uniform vec3 u_light_pos;
uniform vec3 u_light_color;
uniform vec3 u_view_pos;

out vec4 o_color;

void main()
{
    /* Ambient */
    float ambient_strength = 0.3;
    vec3 ambient = ambient_strength * u_light_color;

    /* Diffuse */
    vec3 norm = normalize(v_normal);
    vec3 light_dir = normalize(u_light_pos - v_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * u_light_color;

    /* Specular */
    float specular_strength = 0.5;
    vec3 view_dir = normalize(u_view_pos - v_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * u_light_color;

    /* Final color */
    vec4 tex_color = texture(tex, v_tex_coord);
    vec3 object_color = vec3(tex_color.x, tex_color.y, tex_color.z);
    vec3 result = (ambient + diffuse + specular) * object_color;
    o_color = vec4(result, 1.0);
}

