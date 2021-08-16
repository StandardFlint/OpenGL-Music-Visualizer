//  VertexBufferObject.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/14/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

/*/
 *
 * This class holds information about a single opengl vbo, which it generates upon initialization.
 *
 * Said information includes:
 *                            * The vbo's ID
 *                            * Pointer to the data assosiated with the vbo
 *                            * The size of the data (in bytes)
 *                            * How many components each vertex attribute contains
 *                            * The stride between vertex attributes (byte offset)
 *
 * Any modification of the vbo's data is done through this class.
 * Both the allocation of space on the gpu and upload of the vbo from the cpu to the gpu are handled through this class.
 *
/*/

#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp

#include <stdio.h>
#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <vector>


#define BUFFER_OFFSET(i) (GLvoid*)(i)


class VertexBufferObject{
    
private:
    
    GLuint vertexBufferID;

    GLvoid* data;
    GLsizeiptr dataSize;
    GLint componentSize;
    GLsizei stride;
	unsigned int offset;
    GLenum type;

    
public:
    
	VertexBufferObject();
    VertexBufferObject(GLvoid* _data, GLsizeiptr _dataSize, GLint _componentSize, GLsizei _stride);
	VertexBufferObject(std::vector<GLdouble>* _data, GLint _componentSize, GLsizei _stride);
	VertexBufferObject(std::vector<GLfloat>* _data, GLint _componentSize, GLsizei _stride);
	VertexBufferObject(std::vector<GLint>* _data, GLint _componentSize, GLsizei _stride);
	VertexBufferObject(std::vector<GLshort>* _data, GLint _componentSize, GLsizei _stride);
	
	VertexBufferObject(const VertexBufferObject& original);
	~VertexBufferObject();
    
	VertexBufferObject& operator=(const VertexBufferObject& orig);

    void ConfigureVertexAttributes(GLint _vertexPosition);
    void UpdateVertices(GLvoid* _data, GLsizeiptr _dataSize);

	void UpdateVertices(std::vector<GLdouble>* _data);
	void UpdateVertices(std::vector<GLfloat>* _data);
	void UpdateVertices(std::vector<GLint>* _data);
	void UpdateVertices(std::vector<GLshort>* _data);
    
    GLuint GetVertexBufferID();
    GLvoid* GetData();

	void SetOffset(unsigned int _offset);
	unsigned int GetOffset();
    
    void ChangeStride(GLsizei _newStride);
    void ChangeComponentSize(GLint _newComponentSize);
    
};

#endif /* VertexBufferObject_hpp */

