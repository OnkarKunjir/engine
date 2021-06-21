#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vcolor;

void main(){
    gl_Position = proj * view * model * vec4(position, 1.0);
    // gl_Position = vec4(position, 1.0);
    vcolor = color;
}
