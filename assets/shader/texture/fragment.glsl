#version 330 core

in vec3 vout_color;       // color of vertex for fragment shader.
in vec2 vout_texpos;      // texture coordinate for fragment shader.
in vec3 vout_position;    // world coordinate of vertex.
in vec3 vout_normal;      // normal of vertex.

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;
uniform sampler2D tex;

out vec4 out_color;

void main(){
    float ambient_intensity = 0.5;

    // calculate diffused light.
    vec3 light_direction = normalize(light_position - vout_position);
    float diffused_intensity = max(dot(vout_normal, light_direction), 0.0);

    // calcuate specular light.
    vec3 camera_direction = normalize(camera_position - vout_position);
    vec3 reflection = reflect(-light_direction, vout_normal);
    float specular_intensity =  0.5 * pow(max(dot(camera_direction, reflection), 0.0), 32);

    // calculate total intensity.
    float intensity = ambient_intensity + diffused_intensity + specular_intensity;

    out_color = texture(tex, vout_texpos) * vec4(light_color, 1.0) * (intensity);
}
