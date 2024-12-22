#version 430 core

in vec2 uv;

out vec4 color;

uniform sampler2D displayTex;

void main() 
{
    color = clamp(pow(texture(displayTex, uv), vec4(1.0 / 2.2)), 0.0, 1.0);  //texture(displayTex, uv);
}
