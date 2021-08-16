#version 410 core

uniform float _lineWidth;

uniform vec2 _windowInfo;


layout(lines_adjacency) in;
layout (triangle_strip, max_vertices=8) out;

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
    
    gl_Position = gl_in[0].gl_Position + orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position - orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position + orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position - orthogonalVector;
    EmitVertex();
    
    //////////////////////////////////////////////////////////////////
    
    vector.x = (gl_in[3].gl_Position.x - gl_in[2].gl_Position.x) * (_windowInfo.x / _windowInfo.y);
    vector.y = (gl_in[3].gl_Position.y - gl_in[2].gl_Position.y) * (_windowInfo.y / _windowInfo.x);
    
    unitVector = normalize(vector);
    
    orthogonalVector.x = -unitVector.y * (_lineWidth / _windowInfo.x);
    orthogonalVector.y = unitVector.x * (_lineWidth / _windowInfo.y);
    orthogonalVector.z = 0.0;
    orthogonalVector.w = 0.0;
    
    gl_Position = gl_in[2].gl_Position + orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position - orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[3].gl_Position + orthogonalVector;
    EmitVertex();
    gl_Position = gl_in[3].gl_Position - orthogonalVector;
    EmitVertex();
    
    //////////////////////////////////////////////////////////////////
    
    EndPrimitive();
    
}





/*
void main(){
    
    //////////
    int _thickness = 2;
    vec2 _windowInfo = vec2(1440, 900);
    vec2 _offset = vec2(0, 0);
    float _div = 0;
    float _xPosition = 0;
    float _prevPos = 0;

    /////////////

	if(_prevPos <= -99){

		_prevPos = gl_in[0].gl_Position.y;
		_xPosition += _div;

	}
	else{

		vec2 vector;
		vector.x = _div * (_windowInfo.x / _windowInfo.y);
		vector.y = (gl_in[0].gl_Position.y - _prevPos) * (_windowInfo.y / _windowInfo.x);

		vec2 unitVector;
		unitVector = normalize(vector);

		vec4 orthogonalVector;
		orthogonalVector.x = -unitVector.y * (_thickness / _windowInfo.x);
		orthogonalVector.y = unitVector.x * (_thickness / _windowInfo.y);
		orthogonalVector.z = 0.0;
		orthogonalVector.w = 0.0;

		gl_Position = vec4(_div * gl_VertexID, gl_in[0].gl_Position.y, 1.0, 1.0) + orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
		EmitVertex();
		gl_Position = vec4(_div * gl_VertexID, gl_in[0].gl_Position.y, 1.0, 1.0) - orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
		EmitVertex();
		gl_Position = vec4(_div * gl_VertexID - _div, _prevPos, 1.0, 1.0) + orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
		EmitVertex();
		gl_Position = vec4(_div * gl_VertexID - _div, _prevPos, 1.0, 1.0) - orthogonalVector + vec4(_offset.x, _offset.y, 0.0, 0.0);
		EmitVertex();

		EndPrimitive();

		_prevPos = gl_in[0].gl_Position.y;
		_xPosition += _div;
	
	}


}
*/
