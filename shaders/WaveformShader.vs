#version 410 core

layout(location = 0) in float position;

uniform int _sampleOffset;
uniform float _inc;

uniform float _xOffset;
uniform float _yOffset;

uniform float _amplitude;

void main(){
    
    float xPosition = gl_VertexID * _inc - _sampleOffset * _inc + _xOffset;
    float yPosition = (position / 32767) * _amplitude + _yOffset;
    
    gl_Position = vec4(xPosition, yPosition, 1.0, 1.0);
    //gl_PointSize = 10.0;

}
