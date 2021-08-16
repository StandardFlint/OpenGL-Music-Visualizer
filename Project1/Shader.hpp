//  Shader.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/17/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

/*/
 *
 * This class reads, compiles, and creates a new shader program from vertex and fragment shader files written in glsl.
 * The shader program is created from two necessary shader files, who's locations are arguments for the constructor.
 * An object of type "Shader" holds the shader ID of the shader it creates.
 * It is able to return the number of variables the created shader program contains.
 * Once created, the shader program contained in object "Shader" is not modifiable
 *
/*/

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
//#define GLEW_STATIC
//#include <OpenGL/gl3.h>
#include "GL/glew.h"

class Shader{
    
private:
    
    GLuint shaderID;
    int numberOfVariables;
    GLuint compileShader(GLenum shader, const char* source);
    char* ReadShader(std::string shaderSource);
    void FindNumberOfVariables();

public:
    
    Shader(std::string vertexSource, std::string fragmentSource);
	Shader(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    ~Shader();
    GLuint GetShader();
    GLint GetNumberOfVariables();
	void Bind();
    
};

#endif /* Shader_hpp */
