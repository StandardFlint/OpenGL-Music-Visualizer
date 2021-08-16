#include "IndexBuffer.h"


/*
IndexBuffer::IndexBuffer() {

	indexBufferID = -1;
	data = nullptr;
	dataSize = 0;

}
*/

IndexBuffer::IndexBuffer(GLvoid* _data, GLsizeiptr _dataSize) {

	glGenBuffers(1, &indexBufferID);
	UpdateIndices(_data, _dataSize);

}


IndexBuffer::IndexBuffer(std::vector<GLuint>* _data) {

	glGenBuffers(1, &indexBufferID);
	UpdateIndices(_data);

}


IndexBuffer::~IndexBuffer() {

	glDeleteBuffers(1, &indexBufferID);
	indexBufferID = 0;

}


void IndexBuffer::Bind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

}


void IndexBuffer::UpdateIndices(GLvoid* _data, GLsizeiptr _dataSize) {

	data = _data;
	dataSize = _dataSize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

}


void IndexBuffer::UpdateIndices(std::vector<GLuint>* _data) {

	data = _data->data();
	dataSize = _data->size()*sizeof(GLuint);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

}