#version 330 core
in vec3 in_position;  // location of vertex.
in vec3 in_color;     // color of vertex.
in vec2 in_texpos;    // texture coordinates.
in vec3 in_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vout_color;       // color of vertex for fragment shader.
out vec2 vout_texpos;      // texture coordinate for fragment shader.
out vec3 vout_position;    // world coordinate of vertex.
out vec3 vout_normal;      // normal of vertex.

void main(){
    gl_Position = proj * view * model * vec4(in_position, 1.0);

    vout_color = in_color;
    vout_texpos = in_texpos;
    vout_position = vec3(model * vec4(in_position, 1.0));
    vout_normal = in_normal;
}
