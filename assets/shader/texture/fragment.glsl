#version 330 core

in vec3 vcolor;
in vec2 vtexcord;
in vec4 vposition;
in vec3 vnormal;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 cam_pos;

out vec4 out_color;

uniform sampler2D tex0;
void main(){
    float ambient_light = 0.2;

    vec4 normal = vec4(normalize(vnormal), 1.0);
    vec4 light_direction = normalize(vec4(light_pos, 1.0) - vposition);
    float intensity = max(dot(normal, light_direction), 0.0);

    float specular = 0.5;
    vec4 view_direction = normalize(vec4(cam_pos, 1.0) - vposition);
    vec4 reflect_direction = reflect(-view_direction, normal);
    float spec_amount = pow(max(dot(view_direction, reflect_direction), 0.0), 8);
    specular = specular * spec_amount;

    out_color = texture(tex0, vtexcord) * vec4(light_color, 1.0) * (intensity + ambient_light + specular);
}
