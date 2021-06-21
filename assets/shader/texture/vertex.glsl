#version 330 core

in vec3 position;
in vec3 color;
in vec2 texcord;
in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vcolor;
out vec2 vtexcord;
out vec4 vposition;
out vec3 vnormal;

void main(){
    vposition = model * vec4(position, 1.0);
    gl_Position = proj * view * vposition;

    vcolor = color;
    vtexcord = texcord;
    vnormal = normal;
}
