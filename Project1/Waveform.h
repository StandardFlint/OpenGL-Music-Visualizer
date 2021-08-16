#pragma once

//#include <vector>
//#include <string>
//#include <sndfile.h>
//#include <iostream>

//#include "Window.hpp"

//#include "OpenAL/al.h"
//#include "OpenAL/alc.h"



//#include <chrono>


#include "AudioVisual.hpp"



class Waveform : public AudioVisual{

private:


	float amplitude;

	float width;
    
    float centerOffset;
    int sampleOffset;
    
	int xOffset;
    
    int tempOffset;
    
    float lineWidth;
    
	int range;

	double subdivision;



public:


	Waveform(float _xPosition, float _yPosition, float _width, float _amplitude, int _range, int _center, int _shaderType, GLuint _shaderID);
	~Waveform();


	void SetRange(GLsizei _range);

    void SampleOffset(int _offset);
    void SetAmplitude(float _amplitude);
    
    void SetLineWidth(float _lineWidth);

	void Render();


};
