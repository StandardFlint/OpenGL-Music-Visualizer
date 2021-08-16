#version 410 core

uniform vec4 _inColor;

in vec2 pos;

out vec4 color;

void main(){
    color = _inColor;
	//if(pos.y*10 <= sin(pos.x*10))
	//color = vec4(0.0, 0.0, 0.0, 1.0);
}
