//  Rectangle.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/17/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.

#include "Rectangle.h"


Rectangle::Rectangle(float _xPos, float _yPos, float _width, float _height, unsigned int _constraintType, int _shaderType, GLuint _shaderID) : ScreenObject(_shaderType, _shaderID, GL_TRIANGLES, 6) {

	width = _width;
	height = _height;

	xOriginal = _xPos;
	yOriginal = _yPos;
	xInitial = _xPos;
	yInitial = _yPos;

	windowWidth = 1000;
	windowHeight = 1000;
	refWidth = 1000;
	refHeight = 1000;

	if (_constraintType <= 1)
		constraintType = _constraintType;
	else
		constraintType = RELATIVE;

	centered = false;

	InitVert();
	InitTex();
	InitIndices();

	AddVertexBuffer(&textVerts, 2, 0);
	AddVertexBuffer(&textUVs, 2, 0);
	SetIndexBuffer(&indices);

	SetObjectColor(1.0, 1.0, 1.0, 1.0);

}



Rectangle::~Rectangle() {




}




void Rectangle::InitVert() {

	textVerts.clear();

	float w;
	float h;

	if (constraintType == RELATIVE) {
		w = width;
		h = height;
	}
	else if (constraintType == ABSOLUTE){
		w = width * ((float)refWidth / windowWidth);
		h = height * ((float)refHeight / windowHeight);
	}

	float x = xInitial;
	float y = yInitial;

	float currentVerts[] = { x,     y,
							 x + w, y,
						     x,     y + h,
							 x + w, y + h };

	textVerts.insert(textVerts.end(), currentVerts, currentVerts + 8);

}


void Rectangle::InitTex() {

	textUVs.clear();


	float x = 0;
	float y = 0;

	float w = 1;
	float h = 1;


	float currentUVs[] = { x,     y + h,
						   x + w, y + h,
						   x,     y,
						   x + w, y     };


	textUVs.insert(textUVs.end(), currentUVs, currentUVs + 8);

}



void Rectangle::InitIndices() {

	indices.clear();

	unsigned int currentIndices[] = { 0,
									  1,
									  2,

									  3,
									  2,
									  1 };

	indices.insert(indices.end(), currentIndices, currentIndices + 6);

	if (GetIndexBuffer() != nullptr)
		GetIndexBuffer()->UpdateIndices(&indices);

}



void Rectangle::WindowUpdate(int _width, int _height) {

	windowWidth = _width;
	windowHeight = _height;

	if (centered == false) {
		xInitial = xOriginal;
		yInitial = yOriginal;
	}
	else {
		if (constraintType == RELATIVE) {
			xInitial = xOriginal - (width / 2);
			yInitial = yOriginal - (height / 2);
		}
		else if (constraintType == ABSOLUTE) {
			xInitial = xOriginal - (width * ((float)refWidth / windowWidth) / 2);
			yInitial = yOriginal - (height * ((float)refHeight / windowHeight) / 2);
		}
	}

	UpdateVertices();

}




void Rectangle::UpdateVertices() {

	InitVert();
	GetVertexBuffer(0)->UpdateVertices(&textVerts);
	InitIndices();

}


void Rectangle::UpdateUVs() {

	InitTex();
	GetVertexBuffer(1)->UpdateVertices(&textUVs);

}


void Rectangle::Center() { //costly, make sure to optimize

	if (centered == false) {
		centered = true;
		if (constraintType == RELATIVE) {
			xInitial = xOriginal - (width / 2);
			yInitial = yOriginal - (height / 2);
		}
		else if (constraintType == ABSOLUTE) {
			xInitial = xOriginal - (width * ((float)refWidth / windowWidth) / 2);
			yInitial = yOriginal - (height * ((float)refHeight / windowHeight) / 2);
		}
		UpdateVertices();
	}

}


void Rectangle::Uncenter() {

	if (centered == true) {
		centered = false;
		xInitial = xOriginal;
		yInitial = yOriginal;
		UpdateVertices();
	}

}


bool Rectangle::IsCentered() {

	return centered;

}

void Rectangle::Render() {

	ScreenObject::Render();

}