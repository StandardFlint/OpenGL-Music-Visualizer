//
//  ScreenObject.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/17/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#ifndef ScreenObject_hpp
#define ScreenObject_hpp

#include <stdio.h>
#include <vector>


#include "VertexBufferObject.hpp"
#include "TextureBufferObject.h"
#include "Shader.hpp"
#include "IndexBuffer.h"

#include <iostream>


//#include <OpenGL/gl3.h>
#include "GL/glew.h"

#define FULL_RENDER 0

#define PARTIAL_RENDER 1



class ScreenObject{
    
private:

	TextureBufferObject* textureBuffer;

	IndexBuffer* indexBuffer;

	std::vector<VertexBufferObject*> vertexBuffers;

	unsigned int vertBuffSize;
	unsigned int shaderType;
	GLenum mode;

	unsigned int offsetIndex;
	
	GLsizei vertexCount; //count of vertices
	GLsizei count; //count of total elements


	float* color;
	GLuint shaderID;

	bool renderType;
    
    GLint firstIndex;
    


    
public:

	unsigned int z;
    
	ScreenObject();
	ScreenObject(int _shaderType, GLenum _mode, GLsizei _count);
    ScreenObject(int _shaderType, GLuint _shaderID, GLenum _mode, GLsizei _count);
	//ScreenObject(const ScreenObject& original);                  <- Add later
    ~ScreenObject();
    
    void AddVertexBuffer(GLvoid* _data, GLsizeiptr _dataSize, GLint _componentSize, GLsizei _stride);
	void AddVertexBuffer(std::vector<GLdouble>* _data, GLint _componentSize, GLsizei _stride);
	void AddVertexBuffer(std::vector<GLfloat>* _data, GLint _componentSize, GLsizei _stride);
	void AddVertexBuffer(std::vector<GLint>* _data, GLint _componentSize, GLsizei _stride);
	void AddVertexBuffer(std::vector<GLshort>* _data, GLint _componentSize, GLsizei _stride);

	void SetIndexBuffer(std::vector<GLuint>* _data);

	void SetTextureBuffer(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType);
	void SetTextureBuffer(TextureBufferObject* _texture);

	void ChangeMode(GLenum _mode);

	TextureBufferObject* GetTexture();
	VertexBufferObject* GetVertexBuffer(int _index);
	IndexBuffer* GetIndexBuffer();

	unsigned int GetShaderType();
	GLuint GetShaderID();

	unsigned int VertexBufferSize();

	void SetShaderType(int _type);
	void SetShaderID(GLuint _id);
	void SetVertexCount(GLsizei _count);

    void SetOffset(GLint _offset);
    int GetOffset();
	void SetCount(GLsizei _count);
	int GetCount();

	void SetVertexBufferOffset(int _index, unsigned int _offset, int _type);
	unsigned int GetVertexBufferOffset(int _index);

	GLsizei GetVertexCount();


	void SetObjectColor (float _r, float _g, float _b, float _a);

	virtual void WindowUpdate(int _width, int _height) {}

	virtual void Render();
    

};

#endif /* ScreenObject_hpp */



/*

void main(){

vec4 inColor = _inColor;
int size = _size;

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

if(size < 40)
color = (color / (radius*radius)) * inColor * 1.5;
else if(size < 100)
color = (color / (radius*radius)) * inColor * 1.25;
else if(size < 300)
color = (color / (radius*radius)) * inColor * 1.125;
else
color = (color / float(radius*radius)) * inColor * 1.075;

*/
