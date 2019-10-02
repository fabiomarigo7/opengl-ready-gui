#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

out vec2 FragTex;

uniform mat4 projection;
uniform float max_x;
uniform float max_y;
uniform int startChar;
uniform int currentChar;
uniform float x;
uniform float y;

uniform int hAlign;
uniform int vAlign;

uniform int totalWidth;
uniform int fontHeight;

uniform int shadow;

float current_x;
float current_y;

float x1, y1;

void main()
{
    
    current_x = float((currentChar-startChar)%16);
    current_y = float((currentChar-startChar)/16);
    
    if (hAlign == 0){
        x1 = x;
    }    
    else if (hAlign == 1){
        x1 = x - totalWidth/2.f;
    }
    if (vAlign == 0){
        y1 = y;
    }
    else if (vAlign == 1){
        y1 = y - fontHeight/2.f;
    }
       
    if (shadow == 1){
        x1 = x1 + 1.f;
        y1 = y1 - 1.f;
    }
    
    gl_Position = projection * vec4(pos.x + x1, pos.y + y1, 0.0, 1.0);
	FragTex = vec2(tex.x / max_x + current_x / max_x, tex.y / max_y + current_y / max_y);
}  