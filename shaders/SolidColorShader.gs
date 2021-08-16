#version 410 core

layout(triangles) in;
layout (line_strip, max_vertices=3) out;
 
void main(){

  for(int i = 0; i < gl_in.length(); i++)
  {

	

	float length = sqrt(pow(gl_in[i].gl_Position.x,2) + pow(gl_in[i].gl_Position.y,2));

	vec4 unitVec;
	unitVec.x = gl_in[i].gl_Position.x/length;
	unitVec.y = gl_in[i].gl_Position.y/length;
	unitVec.z = 1.0;
	unitVec.w = 1.0;

     // copy attributes
    gl_Position = unitVec;

    // done with the vertex
    EmitVertex();
  }

  EndPrimitive();


}