//
//  Window.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/18/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>

#include <cstring>

#include "Shader.hpp"

#include "VertexBufferObject.hpp"

#include "ScreenObject.hpp"



#include "TextureBufferObject.h"


#include <vector>

#include "Text.h"


#include "AL/al.h"
#include "AL/alc.h" 


#include <sndfile.h>

#define TEXT_SHADER 0

class Window{
    
private:
    
    GLFWwindow* window;

	ALCdevice* audioDevice;
	ALCcontext* audioContext;

	GLuint vertexAttributeObject;


	std::vector<Shader*> shaders;
	std::vector<ScreenObject*> screenObjects;
	std::vector<Text*> textObjects;

	std::vector<unsigned int> numbScreenObjects;


	std::vector<unsigned int> layerSize;


	std::vector<unsigned int> layerID;


    int width;
    int height;

	int currentWidth;
	int currentHeight;


     
	//TextureBufferObject* tex;
    
    int CreateWindow(int _width, int _height);

	void CreateAudioContext();
    
	//Shader** shaders;
	//unsigned int numberOfShaders;

	//ScreenObject**screenObjects;
	//unsigned int numberOfScreenObjects;

	//unsigned int* numScreenObjects;

	//////
	//float* imgData;

	//int tempCount;
    //////


	///////////////



public:
    
    Window(int _width, int _height);
    ~Window();
    void AddSolidColorObject(GLvoid* _posData, GLsizeiptr _posDataSize, GLsizei _numIndices, float r, float g, float b);
    
    GLFWwindow* GetWindow();
    void Update();
    
	void AddShader(Shader* _shader);

	void AddScreenObject(ScreenObject* _object);

	void AddText(Text* _text);


	void BlankUpdate();

	int GetWidth();
	int GetHeight();
    

    //std::vector<Shader*> shaders;
    
    //std::vector<SolidColor*> solidColorObjects;

    

    //SolidColor* GetSolidColorObject(int _index);
    
    
    //void AddSolidColorSO(GLvoid* _posData, GLsizeiptr _posDataSize, GLsizei _numIndices, float r, float g, float b, Shader* _shader);
    
    //void AddSolidColorSOAt(GLvoid* _data, GLsizeiptr _dataSize, GLint _componentSize, GLsizei _stride, GLenum _mode, GLsizei _numIndices, int _index);

	////////////////////


	//VertexBufferObject* vertexBufferArray;

	//Shader* shader;


    
};
    
    
    
    

#endif /* Window_hpp */
