//
//  ProgramControl.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/19/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#ifndef ProgramControl_hpp
#define ProgramControl_hpp

#include <stdio.h>
#include "Window.hpp"
#include "Shader.hpp"
#include "ScreenObject.hpp"

#include <vector>

#include "lodepng.h"

#include <fstream>

#include <string>

#include "Font.h"

#include "Text.h"

#include "Rectangle.h"

#include "Line2D.h"

#include <cmath>

#include <sndfile.h>

#include "Waveform.h"

#include "Wave.h"

//#include "GLFW/glfw3.h"

//#include <fftw3.h>




/*
 *
 *
 *
 */

//make singleton class
class ProgramControl{
    
private:
    
    bool isRunning;
    Window* mainWindow;

	float* imgData; //
	ScreenObject* obj; //
	Rectangle* object3; //
	Rectangle* object4; //

	Line2D* object5; //

	Rectangle* background; //

	Rectangle* R1; //
	Rectangle* R2; //
    
    ProgramControl(bool _isRunning);
    ~ProgramControl();

	std::vector<float> vPoints;

	std::vector<float>* vPoints2;

	Waveform* wavel;
    Waveform* waver;
    
    Waveform* wavel2;
    Waveform* waver2;
    
    Waveform* wavel3;
    Waveform* waver3;

	Wave* wave2;
    
public:
    
    static ProgramControl& Instance();
    static void Destroy();
    void MainControl();

	Text* testText;
	Text* fps;

};


#endif /* ProgramControl_hpp */
