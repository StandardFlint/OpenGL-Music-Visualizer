#version 410 core

uniform vec4 _inColor;

uniform int _center;

out vec4 color;


void main(){
    

        color = _inColor;
    
    //if(mod(gl_PrimitiveID, 2) == 0)
    //if(gl_FragCoord.y/900.0 < 1)
    
    //if(gl_PrimitiveID > _center - 4 && gl_PrimitiveID < _center + 4)
        //color = vec4(1.0, 0.0, 0.0, 1.0);
    //else
        //color = vec4(0.0, 0.0, 0.0, 1.0);
}
