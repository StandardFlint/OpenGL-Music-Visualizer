#version 410 core

uniform float _lineWidth;

uniform vec2 _windowInfo;

uniform vec2 _offset;

layout(lines) in;
layout (triangle_strip, max_vertices = 4) out;

void main(){

	vec2 vector;
	vector.x = (gl_in[1].gl_Position.x - gl_in[0].gl_Position.x) * (_windowInfo.x / _windowInfo.y);
	vector.y = (gl_in[1].gl_Position.y - gl_in[0].gl_Position.y) * (_windowInfo.y / _windowInfo.x);

	vec2 unitVector;
	unitVector = normalize(vector);

	vec4 orthogonalVector;
	orthogonalVector.x = -unitVector.y * (_lineWidth / _windowInfo.x);
	orthogonalVector.y = unitVector.x * (_lineWidth / _windowInfo.y);
	orthogonalVector.z = 0.0;
	orthogonalVector.w = 0.0;

	gl_Position = gl_in[0].gl_Position + orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
    EmitVertex();
	gl_Position = gl_in[0].gl_Position - orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
    EmitVertex();
	gl_Position = gl_in[1].gl_Position + orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
    EmitVertex();
	gl_Position = gl_in[1].gl_Position - orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
    EmitVertex();

	EndPrimitive();

}
