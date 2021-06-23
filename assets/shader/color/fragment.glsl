#version 330 core
in vec3 vout_color;

out vec4 out_color;

void main(){
    out_color = vec4(vout_color, 1.0);
}
