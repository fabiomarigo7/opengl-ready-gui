#version 330 core

in vec2 FragTex;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec4 color;
uniform int shadow;

void main()
{
    if (shadow == 0){
        FragColor = vec4(color.xyz, texture(tex, FragTex).a);
    }
    if (shadow == 1){
        FragColor = vec4(vec3(0.f, 0.f, 0.f), texture(tex, FragTex).a);
    }
}