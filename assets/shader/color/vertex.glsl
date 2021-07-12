#version 330 core
in vec3 in_position;  // location of vertex.
in vec3 in_color;     // color of vertex.

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vout_color;  // color of vertex for fragment shader.

void main(){
    gl_Position = proj * view * model * vec4(in_position, 1.0f);
    vout_color = in_color;
}
