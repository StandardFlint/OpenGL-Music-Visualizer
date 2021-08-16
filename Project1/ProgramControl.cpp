//
//  ProgramControl.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/19/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#include "ProgramControl.hpp"



ProgramControl::ProgramControl(bool _isRunning) : isRunning(_isRunning){

    float points[12] = {0.0, 0.0, 
						0.5, 0.0, 
						0.0, 0.5,

						0.5, 0.5, 
						0.0, 0.5, 
						0.5, 0.0 };

	float points2[12]= {0.0, 1.0,
						0.0, 0.0,
						1.0, 1.0,

						1.0, 1.0,
						0.0, 0.0,
						1.0, 0.0 }; //flip y-coordinates

	vPoints = { -1, -1,
				-1, 1,
				1, -1,
		 
				1, -1,
				-1, 1,
				1, 1 };

	



	/*float xs = 114.0 / 1024;
	float ys = 118.0 / 1024;

	float points2[12] = { 0.0, ys,
		0.0, 0.0,
		xs, ys,

		xs, ys,
		0.0, 0.0,
		xs, 0.0 };
		*/


	std::vector<unsigned char> image;

	unsigned int width, height;

	lodepng::decode(image, width, height,
		"C:\\Users\\Kevin\\source\\repos\\Project1\\images\\background.png");


    mainWindow = new Window(1280, 720); ///////////////////////////////////////////////////////////////////////

	Shader* shad = new Shader("C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\TextShader.vs",
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\TextShader.fs");

	Shader* shad2 = new Shader("C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\TextureShader.vs",
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\TextureShader.fs");

	Shader* shad3 = new Shader("C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\SolidColorShader.vs",
		/*"\\Users\\Kevin\\Documents\\Visual Studio 2015\\Projects\\NeuralNetworkCreator\\NeuralNetworkCreator\\shaders\\SolidColorShader.gs",*/
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\SolidColorShader.fs");

	Shader* shad4 = new Shader("C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\LineShader.vs",
		//"/Users/kevin/Documents/Project/shaders/LineShaderSegmented.gs",
        "C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\LineShaderContinuous.gs",
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\LineShader.fs");

	Shader* shad5 = new Shader("C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\WaveformShader.vs",
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\WaveformShader.gs",
		"C:\\Users\\Kevin\\source\\repos\\Project1\\shaders\\WaveformShader.fs");


	mainWindow->AddShader(shad);

	mainWindow->AddShader(shad2);
	mainWindow->AddShader(shad3);

	mainWindow->AddShader(shad4);
    
    mainWindow->AddShader(shad5);


	GLuint lineShaderID = shad4->GetShader();

	GLuint waveShaderID = shad5->GetShader();

	wave2 = new Wave("C:\\Users\\Kevin\\source\\repos\\Project1\\audio\\HOS.wav");

	//wave2->LoadAllIntoBuffer();
    
	wave2->BeginStream(44100*2, 0, 1);
    
    //wave2->SetPitch(0.75);
    
    int sampleShow = 440 * 4; //A4 * N
    int center = sampleShow/2;
    float amplitude = 0.95;
    
    float xOffset = -1;
    float yOffset = 0.0;
    
    float length = 2;
    
	wavel = new Waveform(xOffset, yOffset, length, amplitude, sampleShow, center, 4, waveShaderID);
    waver = new Waveform(xOffset, yOffset, length, amplitude, sampleShow, center, 4, waveShaderID);

    
	wave2->AddVisual(wavel);
    wave2->AddVisual(waver);
    
    waver->SetChannel(RIGHT_CHANNEL);
    
    //wavel->SetObjectColor(255.0/255.0, 164.0/255.0, 255.0/255.0, 1.0);
    //waver->SetObjectColor(164.0/255.0, 255.0/255.0, 255.0/255.0, 1.0);
    
    //wavel->SetLineWidth(2.0);
    
    
    
    //waver->z = 1;
    


    wavel2 = new Waveform(xOffset, yOffset, length, amplitude, sampleShow, center, 4, waveShaderID);
    waver2 = new Waveform(xOffset, yOffset, length, amplitude, sampleShow, center, 4, waveShaderID);
    
    wave2->AddVisual(wavel2);
    wave2->AddVisual(waver2);
    
    waver2->SetChannel(RIGHT_CHANNEL);
    
    wavel2->SetObjectColor(64.0/255.0, 64.0/255.0, 96.0/255.0, 0.333);
    waver2->SetObjectColor(64.0/255.0, 64.0/255.0, 96.0/255.0, 0.333);
    
    
    wavel2->SetLineWidth(8);
    waver2->SetLineWidth(8);
    
    
     
     /*
    //wave->SetLineWidth(10);
    
    wave2->AddWaveform(wavel2);
    wave2->AddWaveform(waver2);
    
    waver2->SetChannel(RIGHT_CHANNEL);
    
    wavel2->SetObjectColor(1.0, 1.0, 0.0, 1.0);
    waver2->SetObjectColor(1.0, 1.0, 0.0, 1.0);
    
    //blue
    wavel3 = new Waveform( -1, 0, 2.0, 0.84, sampleShow, 4, waveShaderID);
    waver3 = new Waveform( -1, 0, 2.0, 0.84, sampleShow, 4, waveShaderID);
    
    //wave->SetLineWidth(10);
    
    wave2->AddWaveform(wavel3);
    wave2->AddWaveform(waver3);
    
    waver3->SetChannel(RIGHT_CHANNEL);
    
    wavel3->SetObjectColor(1.0, 0.0, 1.0, 1.0);
    waver3->SetObjectColor(1.0, 0.0, 1.0, 1.0);
    */

    //wave->SetRange(500);
    //wave->SetOffset(500);

	
	//std::cout << audioInfo.frames << std::endl;
	
	//std::cout << audioInfo.samplerate << std::endl;

	//std::cout << audioInfo.channels << std::endl;

	//obj = new ScreenObject(1, GL_TRIANGLES, 6);

	//obj->AddVertexBuffer(&vPoints, 2, 0); ///

	//obj->AddVertexBuffer(points, sizeof(points), 2, 0);

	//obj->AddVertexBuffer(points2, sizeof(points2), 2, 0); ///


	//obj->SetObjectColor(1, 1, 1, 1); //
	

	//object3 = new Rectangle(-0.6, -0.4, .5, .5, 0, 2, shaderID2);
	//object3 = new Rectangle(-0.5, -0.4, .5, .3, 2, shaderID2);
	//object3->SetObjectColor(0.9, 0.9, 0.9, .4); //
	//object3->z = 2;
	//

	GLuint shaderID2 = shad3->GetShader();

	background = new Rectangle(0.0, 0.0, 2, 2, 0, 2, shaderID2);
	background->SetObjectColor(0.1, 0.1, 0.1, 1); //
	//background->z = 3;

	background->Center();


	R1 = new Rectangle(0.0, 0.0, 2, 1.9, 0, 2, shaderID2);
	R1->SetObjectColor(16.0/255, 16.0 / 255, 16.0 / 255, 1.0); //
	//R1->z = 2;

	R1->Center();



	GLuint shaderID = shad2->GetShader();

	//object4 = new Rectangle(-0.8, -0.6, .5, .3, 1, shaderID);
	object4 = new Rectangle(-0.1, 0.7, .5, -.5, 1, 1, shaderID);
	object4->SetObjectColor(0.7, 0.2, 0.4, 1); //
	object4->SetTextureBuffer(image.data(), image.size()*sizeof(char), GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE);
	object4->z = 1;

	//object4->Center();


	object5 = new Line2D(16, 3, lineShaderID);
	object5->SetObjectColor(0.2, 0.6, 1.0, 1); //
	object5->z = 4;
	object5->ChangeMode(GL_LINE_STRIP_ADJACENCY);



	Font* sans = new Font("C:\\Users\\Kevin\\source\\repos\\Project1\\fonts\\Microsoft_Sans_Serif_0.png", "C:\\Users\\Kevin\\source\\repos\\Project1\\fonts\\Microsoft_Sans_Serif.fnt");
	Font* calibri = new Font("C:\\Users\\Kevin\\source\\repos\\Project1\\fonts\\Calibri_Light_0.png", "C:\\Users\\Kevin\\source\\repos\\Project1\\fonts\\Calibri_Light.fnt");

	//std::cout << sans->GetCharInfo(116)->xPos << std::endl;


	std::string someText = "Apple is planning a major overhaul of the\niPhone for 2017, including the adoption of an\nall-new curved glass casing paired with a\ncurved 5.8-inch AMOLED display, according to\nKGI Securities analyst Ming-Chi Kuo.";
	std::string someText2 = "XXXXX\nXXXXX\nXXXXX";
	std::string someText4 = "AaBbCc";

	std::string someText5 = "AA";

	std::string someText3 = "There are generally four things to look at initially.\n"
		"CPU performance : If your code is so slow that it's not feeding the graphics pipe at the maximum rate it could go - then improving the nature of the things you actually draw won't help much.\n"
		"Bus bandwidth : There is a finite limit to the rate at which data can be sent from the CPU to the graphics card.If you require too much data to describe what you have to draw - then you may\n"
		"be unable to keep the graphics card busy simply because you can't get it the data it needs.\n"
		"Vertex performance : The first thing of any significance that happens on the graphics card is vertex processing.A Vertex Shader can be a bottleneck.This is usually easy to diagnose by replacing\n"
		"the shader with something(for example) without lighting calculations and see if things speed up.If they do - then the odds are good that you are vertex limited.\n"
		"Fragment performance : After vertex processing, the polygons are chopped up into fragments(typically the size of a pixel) and the fragment processing takes over.Fragment processing takes longer\n"
		"for large polygons than for small ones - and generally gets slower the more textures you use - and the more complex your fragment shader is.\n"
		"If you are fragment processing bound, a really simple test is to reduce the size of the window you are rendering into down to the size of a postage stamp and see if your frame rate improves.\n"
		"If it does then you are at least partially fill rate limited - if it doesn't then that's not the problem.This is such a simple test that it should always be the first thing you try.\n"
		"There are more subtleties here - but this is a start.";

	GLuint shadID = shad->GetShader();


	testText = new Text(someText2, 150, 0.0, 0.0, calibri, shadID);
	fps = new Text("NULL", 90, -1.0, 1.0, calibri, shadID);

	//"Finally, some real text on the screen\nAuthor: Kevin Flint\n3/20/2016"





	//std::cout << shad->GetShader() << std::endl;

    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    std::cout << "Shader language verions: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    


	//obj->SetTextureBuffer(sans->GetFontTexture());

	testText->SetObjectColor(0.2, 0.2, 0.2, 1);
	
	fps->SetObjectColor(0.25, 0.25, 0.25, 0.25);


	

	//mainWindow->AddText(testText);
	//mainWindow->AddText(fps);

	mainWindow->AddScreenObject(wavel);
    mainWindow->AddScreenObject(waver);
    
    mainWindow->AddScreenObject(wavel2);
    mainWindow->AddScreenObject(waver2);

	
	//mainWindow->AddScreenObject(R1);
	//mainWindow->AddScreenObject(background);

	//mainWindow->AddScreenObject(object5);
	
	//mainWindow->AddScreenObject(object4);
	

	//testText->Center();


    
    //mainWindow->AddSolidColorObject(points, sizeof(points), 3, 0.2, 0.7, 0.5);
    


    

	float radius = .3;
	float PI = 3.14159;


	for (float degree = 0; degree <= 360; degree += 10) {

		float theta = (degree * PI) / 180;
		
		float x = radius*cos(theta) * (1000.0 / mainWindow->GetWidth());
		float y = radius*sin(theta) * (1000.0 / mainWindow->GetHeight());

		object5->AddPoint(x, y);

	}

	radius = .15;

	for (float degree = 0; degree <= 360; degree += 10) {

		float theta = (degree * PI) / 180;

		float x = radius*cos(theta) * (1000.0 / mainWindow->GetWidth());
		float y = radius*sin(theta) * (1000.0 / mainWindow->GetHeight());

		object5->AddPoint(x, y);

	}


	//object5->DeleteSegment(361);


	//object5->SetVertexBufferOffset(0, 0 * sizeof(float));

	//object5->SetCount(20);
 
 
    
}



ProgramControl::~ProgramControl(){
    
    
}


void ProgramControl::MainControl(){

    //int sShow = 220;
    double divTime = 0.01666666;
    double divTime2 = divTime;//0.10706;
    
	int counter2 = 0;

	int counter = 0;////
	int flip = 0;

	double lastTime = glfwGetTime();
	double lastTime2 = lastTime;
    double lastTime3 = lastTime;
	int nbFrames = 0;

	wave2->Play();
    wave2->SyncAllWaveforms();
    mainWindow->Update();
    
    while(isRunning){ //main program loop
        
        isRunning = !glfwWindowShouldClose(mainWindow->GetWindow());

		double currentTime = glfwGetTime();
		//nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			//printf("%f ms/frame\n",  double(nbFrames));
			//1000.0 /
			fps->UpdateText( "Frames per second: " + std::to_string(nbFrames) );

			

			//mainWindow->Update();
			nbFrames = 0;
			lastTime = currentTime;
		}
        /*
        if (currentTime - lastTime3 >= divTime2) {
            
            
            
            wave2->SyncAllWaveforms();
            lastTime3 = currentTime;
            
            counter2++;
            
            if (counter2%10 == 0){
                //divTime2 += 0.0001;
            }
        }
        */
        
		if (currentTime - lastTime2 >= divTime) { //0.016666
			
			nbFrames++;
			//testText->NewSize(counter*2 + 128);
			
			lastTime2 = currentTime;
			mainWindow->Update();
			//testText->NewPosition(counter / 1000.0, 0);

			//std::cout << object5->GetAbsoluteVertexCount() << std::endl;


			wave2->UpdateStream();

            wave2->SyncAllWaveforms();
            
                
            counter2++;
            
            /*
            if(counter2 == 300)
                wave2->GoToSample(44100*60);
            
            if(counter2 == 400)
                wave2->GoToSample(44100*20);
            
            if(counter2 == 500)
                wave2->GoToSample(44100*90);
            */
            
            /*
            if(counter2 == 200)
                wave2->Stop();
            
            if(counter2 == 400)
                wave2->Play();
            */

			//object5->SetVertexBufferOffset(0, counter2 * sizeof(float) * 4);


			//wave->GetLine()->SetVertexBufferOffset(0, counter2 * 16, sizeof(float));

			//wave->SetOffset(0, counter2 * 4 * 100 , sizeof(float) );


			
            
            /*
            if (counter2%10 == 0){
                
                sShow+=2;
                waver->SetRange(sShow);
            }
             */

			double xpos, ypos;
			glfwGetCursorPos(mainWindow->GetWindow(), &xpos, &ypos);



			//std::cout << (xpos/(mainWindow->GetWidth()/2)) - 1 << " : " << 1 - (ypos / (mainWindow->GetHeight() / 2)) << std::endl;



            /*
			if (flip == 0) {
                
				

				counter++;
				if (counter > 256)
					flip = 1;
			}
			if (flip == 1) {

				//testText->NewPosition(0.5, 0.5);
                
				counter--;
				if (counter < 1)
					flip = 0;
			}
              */

			//if (counter == 100)
				//testText->NewPosition(.5,.5);

		}
            



		//mainWindow->BlankUpdate();
		//mainWindow->Update();


    }
    
}


ProgramControl& ProgramControl::Instance(){
    
    static ProgramControl* programControl;
    
    if (programControl == nullptr) {
        
        programControl = new ProgramControl(true);
        
    }
    
    return *programControl;
}


void ProgramControl::Destroy(){
    
    ProgramControl* programControl = &Instance();
    
    if (programControl != nullptr) {
        delete programControl;
    }
    
}
