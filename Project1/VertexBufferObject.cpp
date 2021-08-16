//  VertexBufferObject.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/14/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

#include "VertexBufferObject.hpp"

VertexBufferObject::VertexBufferObject() {

	vertexBufferID = -1;
	data = nullptr;
	dataSize = 0;
	componentSize = 0;
	stride = 0;
	offset = 0;


}


VertexBufferObject::VertexBufferObject(GLvoid* _data, GLsizeiptr _dataSize, GLint _componentSize, GLsizei _stride){
    
    stride = _stride;
    componentSize = _componentSize;
	offset = 0;
    type = GL_FLOAT;

    glGenBuffers(1, &vertexBufferID);
    UpdateVertices(_data, _dataSize);
    
}


VertexBufferObject::VertexBufferObject(std::vector<GLdouble>* _data, GLint _componentSize, GLsizei _stride) {

	stride = _stride;
	componentSize = _componentSize;
	offset = 0;
    type = GL_DOUBLE;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(_data);

}


VertexBufferObject::VertexBufferObject(std::vector<GLfloat>* _data, GLint _componentSize, GLsizei _stride) {

	stride = _stride;
	componentSize = _componentSize;
	offset = 0;
    type = GL_FLOAT;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(_data);

}

VertexBufferObject::VertexBufferObject(std::vector<GLint>* _data, GLint _componentSize, GLsizei _stride) {

	stride = _stride;
	componentSize = _componentSize;
	offset = 0;
    type = GL_INT;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(_data);

}


VertexBufferObject::VertexBufferObject(std::vector<GLshort>* _data, GLint _componentSize, GLsizei _stride) {

	stride = _stride;
	componentSize = _componentSize;
	offset = 0;
    type = GL_SHORT;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(_data);

}



VertexBufferObject::VertexBufferObject(const VertexBufferObject& original) { ///////////////////////

	data = original.data;
	dataSize = original.dataSize;
	componentSize = original.componentSize;
	stride = original.stride;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(data, dataSize);

}

VertexBufferObject::~VertexBufferObject(){
    
    glDeleteBuffers(1, &vertexBufferID);
    vertexBufferID = 0;
    
}


VertexBufferObject& VertexBufferObject::operator=(const VertexBufferObject& original) {

	if (&original == this)
		return *this;

	data = original.data;
	dataSize = original.dataSize;
	componentSize = original.componentSize;
	stride = original.stride;

	glGenBuffers(1, &vertexBufferID);
	UpdateVertices(data, dataSize);

	return *this;

}


void VertexBufferObject::ConfigureVertexAttributes(GLint vertexPosition){
    
    if(vertexPosition != -1){

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);////
        glEnableVertexAttribArray(vertexPosition);
        glVertexAttribPointer(vertexPosition, componentSize, type, GL_FALSE, stride, BUFFER_OFFSET( offset ));
        
    }

    
}

void VertexBufferObject::UpdateVertices(GLvoid* _data, GLsizeiptr _dataSize){
    
    data = _data;
    dataSize = _dataSize;
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
    
}

void VertexBufferObject::UpdateVertices(std::vector<GLdouble>* _data) {

	data = _data->data();
	dataSize = _data->size()*sizeof(GLdouble);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

}

void VertexBufferObject::UpdateVertices(std::vector<GLfloat>* _data) {

	data = _data->data();
	dataSize = _data->size()*sizeof(GLfloat);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

}

void VertexBufferObject::UpdateVertices(std::vector<GLint>* _data) {

	data = _data->data();
	dataSize = _data->size()*sizeof(GLint);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

}


void VertexBufferObject::UpdateVertices(std::vector<GLshort>* _data) {

	data = _data->data();
	dataSize = _data->size()*sizeof(GLshort);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

}



GLuint VertexBufferObject::GetVertexBufferID(){
    
    return vertexBufferID;
    
}

GLvoid* VertexBufferObject::GetData(){
    
    return data;
    
}

void VertexBufferObject::ChangeStride(GLsizei _newStride){
    
    stride = _newStride;
    
}


void VertexBufferObject::SetOffset(unsigned int _offset) {

	offset = _offset;

}


unsigned int VertexBufferObject::GetOffset() {

	return offset;

}



void VertexBufferObject::ChangeComponentSize(GLint _newComponentSize){
    
    componentSize = _newComponentSize;
    
}

















