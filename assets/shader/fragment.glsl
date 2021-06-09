#version 330

in vec3 vcolor;
in vec2 vtexcord;

uniform vec2 scale;

out vec4 out_color;

uniform sampler2D tex0;
void main(){
    out_color = vec4(vcolor, 1.0);
    // out_color = texture(tex0, vtexcord*scale) + vec4(vcolor, 1.0);
}
