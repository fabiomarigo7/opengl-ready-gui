#version 330 core

in vec2 FragTex;
out vec4 FragColor;

uniform sampler2D texture1;
uniform int picking;
uniform vec4 picking_color;


void main()
{
    
    if (picking == 1){
        float alpha = float(1 - int(texture(texture1, FragTex).a == 0.f));
        FragColor = alpha * picking_color;
    }
    else {
        FragColor = texture(texture1, FragTex);
    }
}