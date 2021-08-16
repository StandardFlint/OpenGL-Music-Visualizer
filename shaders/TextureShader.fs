#version 410 core

uniform sampler2D diffuse;

in vec2 texCoord0;

out vec4 color;

void main(){

	color = texture(diffuse, texCoord0);

}