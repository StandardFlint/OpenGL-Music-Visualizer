#version 410 core

uniform sampler2D diffuse;

in vec2 texCoord0;

out vec4 color;

void main(){

	float blurAmount = 6;
	float pixelSize = 0.0001;

	float radius = (blurAmount-1)*2 + 3;

	for( int u = 0; u < radius; u++ ){
		for( int v = 0; v < radius; v++ ){

		float blur = blurAmount*pixelSize;
		vec2 offset = vec2(u * blur, v * blur);
		color += texture( diffuse, texCoord0 + offset);

		}
	}

	color = (color / (radius*radius));

}