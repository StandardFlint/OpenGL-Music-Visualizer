//
//  Window.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/18/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#include "Window.hpp"

#include <stdlib.h>

Window::Window(int _width, int _height) {

	width = _width;
	height = _height;

	CreateWindow(width, height);
	CreateAudioContext();

	glGenVertexArrays(1, &vertexAttributeObject);
	glBindVertexArray(vertexAttributeObject);

}



Window::~Window() {

	audioDevice = alcGetContextsDevice(audioContext);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(audioContext);
	alcCloseDevice(audioDevice);
	glfwDestroyWindow(window);

}



//Create GLFW window
int Window::CreateWindow(int width, int height){


    if (!glfwInit()){
        return -1;
    }
    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_DEPTH_BITS, 32);
    glfwWindowHint (GLFW_RED_BITS, 8);
    glfwWindowHint (GLFW_BLUE_BITS, 8);
    glfwWindowHint (GLFW_GREEN_BITS, 8);
    glfwWindowHint (GLFW_ALPHA_BITS, 8);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    window = glfwCreateWindow(width, height, "Neural Network Creator", nullptr, nullptr);
    
    if (!window){
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND); //

	//glEnable(GL_DEPTH_TEST);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glDepthFunc(GL_LESS);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ////

	//glBlendEquation(GL_FUNC_ADD);
    
    return 0;
    
}


void Window::CreateAudioContext() {
    
    ////////////////////////////
    
    const ALCchar* device;
    
    device = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    
    const ALCchar* next = device+1;
    
    int len = 0;
    
    while (device && *device != '\0' && next && *next != '\0'){
        
        std::cout << device  << std::endl;
        len = strlen(device);
        device += len+1;
        next += len+2;
        
        
    }

    ////////////////////////////

	const ALCchar * defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	audioDevice = alcOpenDevice(defaultDevice);
	if (audioDevice) {
		audioContext = alcCreateContext(audioDevice, NULL);
		alcMakeContextCurrent(audioContext);
		alGetError();
	}
    
    if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_ALL_EXT") == true)
        std::cout << "Extension Found" << std::endl;
    
    

}



void Window::Update(){
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwGetWindowSize(window, &currentWidth, &currentHeight);

	if (width != currentWidth || height != currentHeight) {

		width = currentWidth;
		height = currentHeight;
		
		glViewport(0, 0, width, height);

		for (int i = 0; i < textObjects.size(); i++) {

			textObjects[i]->UpdateTextVert(width, height);

		}

		for (int i = 0; i < screenObjects.size(); i++) {

			screenObjects[i]->WindowUpdate(width, height);

		}

	}


	int layerIndex = 0;

	for (int j = 0; j < layerSize.size(); j++) {

		int index = j * shaders.size();
		int startingIndex = layerIndex;

		//std::cout << "starting point: " << startingIndex << std::endl;

		for (int i = 0; i < shaders.size(); i++) {

			if (i != TEXT_SHADER) {

				//std::cout << "shader: " << i << std::endl;

				shaders[i]->Bind();

				for (int k = startingIndex; k < numbScreenObjects[index + i] + startingIndex; k++) {//

					screenObjects[k]->Render();
					//std::cout << k << std::endl;

				}

				startingIndex += numbScreenObjects[index + i];

			}
		}

		layerIndex += layerSize[j];

	}


	shaders[TEXT_SHADER]->Bind();

	for (int i = 0; i < textObjects.size(); i++) {

		textObjects[i]->Render();

	}
    
    
       
    glfwSwapBuffers(window);
    glfwPollEvents();
    
}


void Window::BlankUpdate() {

	glfwGetWindowSize(window, &currentWidth, &currentHeight);
	if (width != currentWidth || height != currentHeight) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		width = currentWidth;
		height = currentHeight;

		glViewport(0, 0, width, height);

		for (int i = 0; i < textObjects.size(); i++) {

			textObjects[i]->UpdateTextVert(width, height);

		}

		int startingIndex = 0;

		for (int i = 0; i < shaders.size(); i++) {

			if (i != TEXT_SHADER) {

				shaders[i]->Bind();

				for (int  k = startingIndex; k < numbScreenObjects[i]; k++) {

					screenObjects[k]->Render();

				}

				startingIndex += numbScreenObjects[i];

			}
		}

		shaders[TEXT_SHADER]->Bind();

		for (int i = 0; i < textObjects.size(); i++) {

			textObjects[i]->Render();

		}

		glfwSwapBuffers(window);

	}


	glfwPollEvents();

}



GLFWwindow* Window::GetWindow(){
    return window;
}




void Window::AddShader(Shader* _shader) {

	shaders.push_back(_shader);

	if (layerID.size() == 0) {

		numbScreenObjects.push_back(0);

	}
	else {

		int insertionIndex = 0;

		for (int i = 0; i < layerID.size(); i++) {

			numbScreenObjects.insert(numbScreenObjects.begin() + insertionIndex, 0);
			insertionIndex += shaders.size();

		}
	}
}



void Window::AddScreenObject(ScreenObject* _object) {

	int layer = _object->z;

	int layerIndex = 0;

	
	if (layerID.size() == 0) {
		layerID.push_back(layer);
		layerSize.push_back(1);
	}
	else {

		//unsigned int 

		for (int i = 0; i < layerID.size(); i++) {

			if (layerID[i] == layer) {///////////
				layerIndex = i;
				layerSize[i]++;
				break;
			}
			else if (layerID[i] > layer) {///////////////

				layerIndex = i;
				layerID.insert(layerID.begin() + i, layer);
				layerSize.insert(layerSize.begin() + i, 1);

				int insertPos = 0;

				if (layerIndex != 0)
					insertPos = layerIndex * shaders.size();

				for (int k = 0; k < shaders.size(); k++) {

					numbScreenObjects.insert(numbScreenObjects.begin() + insertPos, 0);

				}


				break;

			}
			else if (i == layerID.size() - 1) {////////////////

				layerIndex = i+1; ///////
				layerID.push_back(layer);
				layerSize.push_back(1);

				for (int i = 0; i < shaders.size(); i++) {

					numbScreenObjects.push_back(0);

				}

				break;

			}

		}

	}


//////////////////////////////////////////////////////////////
	

	int startingIndex = 0;
	//int startingIndex2 = 0;




	for (int i = 0; i < layerIndex; i++) {


		for (int k = 0; k < shaders.size(); k++) {

			startingIndex += numbScreenObjects[k];

		}

	}


	try {

		if (_object->GetShaderType() < 0 || _object->GetShaderType() >= shaders.size())
			throw("Error: The object's shader type is not included in this window instance. Could not add.");

		int insertionIndex = startingIndex;

		int index = layerIndex * shaders.size();

		for (int i = 0; i < _object->GetShaderType(); i++) {
			insertionIndex += numbScreenObjects[index + i];
			
		}
		//std::cout << _object->GetShaderType() << std::endl;
		//std::cout << insertionIndex << std::endl;

		_object->WindowUpdate(width, height);
		screenObjects.insert(screenObjects.begin() + insertionIndex, _object);


		numbScreenObjects[index + _object->GetShaderType()]++;


	}
	catch (const char* i) {
		std::cout << i << std::endl;
	}

}



void Window::AddText(Text* _text) {

	_text->UpdateTextVert(width, height);
	textObjects.push_back(_text);

}
    

int Window::GetWidth() {

	return width;

}


int Window::GetHeight() {

	return height;

}
