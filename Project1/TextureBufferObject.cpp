#include "TextureBufferObject.h"

TextureBufferObject::TextureBufferObject(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType) {

	glGenTextures(1, &textureBufferID);
	UpdateTexture(_data, _dataSize, _target, _textureFormat, _width, _height, _dataFormat, _dataType);

}


TextureBufferObject::~TextureBufferObject() {

	glDeleteTextures(1, &textureBufferID);
	textureBufferID = 0;

}


void TextureBufferObject::UpdateTexture(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType) {

	data = _data;
	dataSize = _dataSize;
	target = _target;

	glBindTexture(target, textureBufferID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST GL_LINEAR
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(target, 0, _textureFormat, _width, _height, 0, _dataFormat, _dataType, data);

}


void TextureBufferObject::Bind(int unit) {

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(target, textureBufferID);

}


GLuint TextureBufferObject::GetTextureBufferID() {

	return textureBufferID;

}

GLvoid* TextureBufferObject::GetData() {

	return data;

}