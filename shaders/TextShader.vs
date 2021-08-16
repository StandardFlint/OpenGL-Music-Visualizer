#version 410 core

uniform float _scale;

uniform vec2 _position;

uniform vec2 _centerOffset;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 texCoord;

out vec2 texCoord0;

void main(){

	vec2 scaledPosition;
	scaledPosition.x = (vertexPosition.x  - _centerOffset.x) * _scale;
	scaledPosition.y = (vertexPosition.y - _centerOffset.y) * _scale;

	vec2 newPosition;
	newPosition.x = scaledPosition.x + _position.x;
	newPosition.y = scaledPosition.y + _position.y;

    gl_Position = vec4(newPosition, 1.0, 1.0);
	texCoord0 = texCoord;

}