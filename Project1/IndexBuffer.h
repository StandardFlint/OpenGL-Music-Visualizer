#pragma once



#include <stdio.h>
#include <iostream>
//#define GLEW_STATIC
//#include <OpenGL/gl3.h> ***
//#include "GLFW/glfw3.h"
#include <vector>

#include "GL/glew.h"



class IndexBuffer {

private:

	GLuint indexBufferID;
	GLvoid* data;
	GLsizeiptr dataSize;

public:

	//IndexBuffer();
	IndexBuffer(GLvoid* _data, GLsizeiptr _dataSize);
	IndexBuffer(std::vector<GLuint>* _data);

	~IndexBuffer();

	void UpdateIndices(GLvoid* _data, GLsizeiptr _dataSize);
	void UpdateIndices(std::vector<GLuint>* _data);

	void Bind();

};
