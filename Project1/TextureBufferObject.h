#pragma once



#include <stdio.h>
#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
//#include "GLFW/glfw3.h"




class TextureBufferObject {

private:

	GLuint textureBufferID;
	GLvoid* data;
	GLsizeiptr dataSize;
	GLenum target;

public:

	TextureBufferObject() {}
	TextureBufferObject(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType);
	~TextureBufferObject();

	void UpdateTexture(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType);
	void Bind(int unit);

	GLuint GetTextureBufferID();
	GLvoid* GetData();


};
