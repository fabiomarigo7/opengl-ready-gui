#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

out vec2 FragTex;

uniform mat4 projection;
uniform float x; // x-position in the screen
uniform float y; // y-position in the screen

uniform int char_xpos; // x-position in the font png
uniform int char_ypos; // y-position in the font png
uniform int char_xadvance;
uniform int char_width;
uniform int char_height;
uniform int char_xoffset;
uniform int char_yoffset;
uniform int totalWidth;
uniform int fontHeight;

// text properties

uniform int hAlign;
uniform int vAlign;
uniform int shadow;

void main()
{
    
    float current_x = float(char_xpos);
    float current_y = float(char_ypos);
    float x1, y1;
    
    if (hAlign == 0) x1 = x + 5.f;
    else if (hAlign == 1) x1 = x - totalWidth / 2.f;
    
    if (vAlign == 0) y1 = y + fontHeight;
    else if (vAlign == 1) y1 = y + fontHeight / 2.f;
    
    if (shadow == 1){
        x1 = x1 + 1.f;
        y1 = y1 - 1.f;
    }
    
    float xtex = (current_x) + tex.x * ( char_width ); 
    float ytex = (current_y) + tex.y * ( char_height ); 
    
    gl_Position = projection * vec4(pos.x * char_width + x1 + char_xoffset, pos.y * char_height + y1 - char_yoffset, 0.0, 1.0);
	FragTex = vec2(xtex / 512.f, ytex / 512.f);
}  