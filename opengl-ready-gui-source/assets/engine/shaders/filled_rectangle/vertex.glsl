#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 projection;

uniform float x;
uniform float y;
uniform float w;
uniform float h;
uniform int origin;

void main()
{
    float x1, y1;
    
    if (origin == 0){ // bottom-left
        x1 = x;
        y1 = y;
    }
    
    if (origin == 1) { // top-left    
        x1 = x;
        y1 = y - h;
    }
    
    if (origin == 2){ // center
        x1 = x - w/2.f;
        y1 = y - h/2.f;
    }
    
    gl_Position = projection * vec4(pos.x * w + x1, pos.y * h + y1, pos.z, 1.0);
    
}  