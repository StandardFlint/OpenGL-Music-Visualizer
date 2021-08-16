#version 410 core

uniform int _z;

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 texCoord0;

void main(){
    
    gl_Position = vec4(position, 1.0, 1.0);
	texCoord0 = texCoord;
}
