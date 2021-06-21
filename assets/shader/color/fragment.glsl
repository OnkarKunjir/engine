#version 330 core

in vec3 vcolor;

out vec4 out_color;
void main(){
    out_color = vec4(vcolor, 1.0);
}
