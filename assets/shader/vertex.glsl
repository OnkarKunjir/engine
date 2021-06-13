#version 330

in vec3 position;
in vec3 color;
in vec2 texcord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vcolor;
out vec2 vtexcord;

void main(){
    gl_Position = proj * view * model * vec4(position, 1.0);
    // gl_Position = vec4(position, 1.0);
    vcolor = color;
    vtexcord = texcord;
}
