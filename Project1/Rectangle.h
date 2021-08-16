//  Rectangle.hpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/18/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#include "ScreenObject.hpp"

#define RELATIVE 0
#define ABSOLUTE 1

class Rectangle : public ScreenObject {

private:

	std::vector<float> textVerts;
	std::vector<float> textUVs;
	std::vector<unsigned int> indices;

	float xOriginal;
	float yOriginal;

	float xInitial;
	float yInitial;

	int windowWidth;
	int windowHeight;

	int refWidth;
	int refHeight;

	float width;
	float height;

	int constraintType;

	bool centered;




public:

	Rectangle(float _xPos, float _yPos, float _width, float _height, unsigned int _constraintType, int _shaderType, GLuint _shaderID);
	~Rectangle();

	void InitVert();
	void InitTex();
	void InitIndices();

	void NewSize(int _size);
	void NewPosition(float _x, float _y);

	void WindowUpdate(int _width, int _height);
	void UpdateVertices();
	void UpdateUVs();

	void Center();
	void Uncenter();
	bool IsCentered();

	void Render();


};
