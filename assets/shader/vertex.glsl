#version 330

in vec2 position;
in vec3 color;
in vec2 texcord;

out vec3 vcolor;
out vec2 vtexcord;

void main(){
    gl_Position = vec4(position, 0.0, 1.0);
    vcolor = color;
    vtexcord = texcord;
}
