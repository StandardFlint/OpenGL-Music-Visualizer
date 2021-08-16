#version 410 core

uniform vec4 _inColor;

uniform sampler2D _diffuse;

in vec2 texCoord0;


out vec4 color;

//note: come back and optimize later

void main(){

	vec4 inColor = _inColor;
	int size = 100;

	int blurAmount = 1;
	float pixelSize = 0.0004;

	if(size < 40)
		blurAmount = 3;
	else if(size < 100)
		blurAmount = 2;
	else if(size < 300)
		blurAmount = 1;


	int radius = (blurAmount-1)*2 + 3;
	float blur;
	vec2 offset;

	
	for( int u = 0; u < radius; u++ ){
		for( int v = 0; v < radius; v++ ){

		blur = blurAmount*pixelSize;
		offset = vec2(u * blur, v * blur);
		color += texture( _diffuse, texCoord0 + offset);

		}
	}

	//if(color.a < 0.5)
		//discard;

	if(size < 40)
		color = (color / (radius*radius)) * inColor * 1.5;
	else if(size < 100)
		color = (color / (radius*radius)) * inColor * 1.25;
	else if(size < 300)
		color = (color / (radius*radius)) * inColor * 1.125;
	else
		color = (color / float(radius*radius)) * inColor * 1.075;

}
