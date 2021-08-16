//  Shader.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/17/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

#include "Shader.hpp"

Shader::Shader(std::string vertexSource, std::string fragmentSource){
    
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, ReadShader(vertexSource));
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, ReadShader(fragmentSource));

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    FindNumberOfVariables();
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

Shader::Shader(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {


	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, ReadShader(vertexSource));
	GLuint geometryShader = compileShader(GL_GEOMETRY_SHADER, ReadShader(geometrySource));
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, ReadShader(fragmentSource));


	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, geometryShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	FindNumberOfVariables();

	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader(){
    
    glDeleteProgram(shaderID);
    
}

char* Shader::ReadShader(std::string shaderSource){
    
    char tempSource[10000];
    
    //Open shader files
    std::ifstream sourceFile(shaderSource);
    sourceFile >> std::noskipws;
    
    //Read in shader file by extracting each character into "tempShader"
    int charCount = 0;
    
    while( !sourceFile.eof() ){
        
        sourceFile >> tempSource[charCount];

        //Break if there are no more characters to read (I know this is redundant, will fix later)
        if(sourceFile.eof()){
            break;
        }
        else{
            charCount++;
        }
    }
    
    //Create new char array the size of the number of characters extracted from shader file
    char* source = new char[charCount+1];
    
    //Copy extracted characters into new "tempFragmentSource" array
    for(int i = 0; i < charCount; i++){
        source[i] = tempSource[i];
    }
    
    //Tack on null opperator at the end of the array
    source[charCount] = '\0';
    
    sourceFile.close();
    return source;
    
}

GLuint Shader::compileShader(GLenum _shader, const char* _source){
    
	//std::cout << "success" << std::endl;

    GLuint shaderHandle = glCreateShader(_shader);
    glShaderSource(shaderHandle, 1, &_source, NULL);
    glCompileShader(shaderHandle);

	//
	GLint success = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	std::cout << success << std::endl;
	//

    return shaderHandle;
    
}

void Shader::Bind() {

	GLint val;


	//std::cout << "should be: " << shaderID;

	glUseProgram(shaderID);

	glGetIntegerv(GL_CURRENT_PROGRAM, &val);

	//std::cout << ", is: " << val << std::endl;
	

}

GLuint Shader::GetShader(){
    
    return shaderID;
    
}

int Shader::GetNumberOfVariables(){

    return numberOfVariables;
    
}

void Shader::FindNumberOfVariables(){
    
    GLint numberOfAttributes;
    glGetProgramiv (shaderID, GL_ACTIVE_ATTRIBUTES, &numberOfAttributes);
    GLint numberOfUniforms;
    glGetProgramiv (shaderID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
    numberOfVariables = numberOfAttributes + numberOfUniforms;
    
}
