//  ScreenObject.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/17/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

#include "ScreenObject.hpp"




ScreenObject::ScreenObject() {

	textureBuffer = nullptr;
	indexBuffer = nullptr;
	shaderType = 0;
	mode = GL_TRIANGLES;
	vertexCount = 0;
	count = vertexCount;
	offsetIndex = 0;
    firstIndex = 0;
	renderType = FULL_RENDER;
	color = nullptr;
	shaderID = -1;
	z = 0;

}


ScreenObject::ScreenObject(int _shaderType, GLenum _mode, GLsizei _count) {

	textureBuffer = nullptr;
	indexBuffer = nullptr;
	shaderType = _shaderType;
	mode = _mode;
	vertexCount = _count;
	count = vertexCount;
	offsetIndex = 0;
    firstIndex = 0;
	renderType = FULL_RENDER;
	color = nullptr;
	shaderID = -1;
	z = 0;

}



ScreenObject::ScreenObject(int _shaderType, GLuint _shaderID, GLenum _mode, GLsizei _count){

	textureBuffer = nullptr;
	indexBuffer = nullptr;
	shaderType = _shaderType;
	mode = _mode;
	vertexCount = _count;
	count = vertexCount;
	offsetIndex = 0;
    firstIndex = 0;
	renderType = FULL_RENDER;
	color = nullptr;
	shaderID = _shaderID;
	z = 0;
    
}

//ScreenObject::ScreenObject(const ScreenObject& original) {



//}


ScreenObject::~ScreenObject(){

	/*
	if (vertBuffSize == 1)
		delete vertexBuffers;
	else if(vertBuffSize > 1)
		delete[] vertexBuffers;
		*/

	delete textureBuffer;

	/*
	if (texBuffSize == 1)
		delete textureBuffers;
	else if (texBuffSize > 1)
		delete[] textureBuffers;
	*/
    
}

void ScreenObject::AddVertexBuffer(GLvoid* _data, GLsizeiptr _dataSize, GLint _componentSize, GLsizei _stride){
    

	vertexBuffers.push_back(new VertexBufferObject(_data, _dataSize, _componentSize, _stride));

   
}


void ScreenObject::AddVertexBuffer(std::vector<GLdouble>* _data, GLint _componentSize, GLsizei _stride) {

	vertexBuffers.push_back(new VertexBufferObject(_data, _componentSize, _stride));

}

void ScreenObject::AddVertexBuffer(std::vector<GLfloat>* _data, GLint _componentSize, GLsizei _stride) {

	vertexBuffers.push_back(new VertexBufferObject(_data, _componentSize, _stride));

}

void ScreenObject::AddVertexBuffer(std::vector<GLint>* _data, GLint _componentSize, GLsizei _stride) {

	vertexBuffers.push_back(new VertexBufferObject(_data, _componentSize, _stride));

}

void ScreenObject::AddVertexBuffer(std::vector<GLshort>* _data, GLint _componentSize, GLsizei _stride) {

	vertexBuffers.push_back(new VertexBufferObject(_data, _componentSize, _stride));

}




void ScreenObject::SetIndexBuffer(std::vector<GLuint>* _data) {

	indexBuffer = new IndexBuffer(_data);

}




void ScreenObject::SetTextureBuffer(GLvoid* _data, GLsizeiptr _dataSize, GLenum _target, GLint _textureFormat, GLsizei _width, GLsizei _height, GLenum _dataFormat, GLenum _dataType) {


	textureBuffer = new TextureBufferObject(_data, _dataSize, _target, _textureFormat, _width, _height, _dataFormat, _dataType);

}


void ScreenObject::SetTextureBuffer(TextureBufferObject* _texture) {
	textureBuffer = _texture;
}


void ScreenObject::ChangeMode(GLenum _mode) {

	mode = _mode;

}




TextureBufferObject* ScreenObject::GetTexture() {

	return textureBuffer;

}

IndexBuffer* ScreenObject::GetIndexBuffer() {

	return indexBuffer;

}

 
 VertexBufferObject* ScreenObject::GetVertexBuffer(int _index) {

	 if (vertexBuffers.size() > 0)
		 return vertexBuffers[_index];
	 else
		 return nullptr;

}

unsigned int ScreenObject::GetShaderType() {

	return shaderType;

}


GLuint ScreenObject::GetShaderID() {

	return shaderID;

}


void ScreenObject::SetShaderID(GLuint _id) {

	shaderID = _id;

}

void ScreenObject::SetShaderType(int _type) {

	shaderType = _type;

}

///////////
void ScreenObject::SetVertexCount(GLsizei _count) {


	if(renderType == FULL_RENDER){ 
		vertexCount = _count;
		count = vertexCount;
	}
	else if (renderType == PARTIAL_RENDER) {
		vertexCount = _count;
	}

}

///////////
GLsizei ScreenObject::GetVertexCount() {

	return vertexCount;

}


void ScreenObject::SetOffset(GLint _offset) {
    
    firstIndex = _offset;
    
}


int ScreenObject::GetOffset() {
    
    return firstIndex;
    
}


void ScreenObject::SetCount(GLsizei _count) {
    
    
    count = _count;
    
    
    /*

	int dif = vertexCount - (offsetIndex + _count);

	if (dif >= 0) {
		if (_count >= 0) {
			count = _count;
			renderType = PARTIAL_RENDER;
		}
		else {
			count = vertexCount;
			renderType = FULL_RENDER;
		}
	}
     */

}


int ScreenObject::GetCount() {

	return count;

}






unsigned int ScreenObject::VertexBufferSize() {

	return vertexBuffers.size();

}


void ScreenObject::SetObjectColor(float _r, float _g, float _b, float _a) {

	if (color == nullptr)
		color = new float[4];
	
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
	color[3] = _a;

}

////////
void ScreenObject::SetVertexBufferOffset(int _index, unsigned int _offset, int _type) {


	if (_index < vertexBuffers.size()) {


		int dif = vertexCount - (_offset + count);

		if (dif >= 0) {

			vertexBuffers[_index]->SetOffset(_offset * _type);
			offsetIndex = _offset;

		}

	}

}


unsigned int ScreenObject::GetVertexBufferOffset(int _index) {

	return vertexBuffers[_index]->GetOffset();

}


void ScreenObject::Render() {

	if (vertexBuffers.size() > 0) {

		for (unsigned int i = 0; i < vertexBuffers.size(); i++) {
			vertexBuffers[i]->ConfigureVertexAttributes(i);
		}

		if (textureBuffer != nullptr) {
			textureBuffer->Bind(0);
			//std::cout << "texture included" << std::endl;
		}
		
		if (color != nullptr) {
			GLint loc = glGetUniformLocation(GetShaderID(), "_inColor");
			//std::cout << loc << std::endl;
			if (loc >= 0)
				glUniform4fv(loc, 1, color); 
		}

		//std::cout << count << std::endl;
		if (indexBuffer == nullptr) {
			glDrawArrays(mode, firstIndex, count);
		}
		else {
			
			indexBuffer->Bind();
			glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);

		}
        
        //NOTE: Add glDrawRangeElements later

	}

}





