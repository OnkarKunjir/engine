#version 330 core
in vec2 in_position;  // location of vertex.
in vec3 in_color;     // color of vertex.

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vout_color;  // color of vertex for fragment shader.

void main(){
    gl_Position =  proj * vec4(in_position, 0.0, 1.0);
    vout_color = in_color;
}
