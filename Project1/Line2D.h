#pragma once

#include "ScreenObject.hpp"

class Line2D : public ScreenObject {

private:

	std::vector<float>* linePoints;

	float lineWidth;

	int windowWidth;
	int windowHeight;

	int numberOfSegments;

	float xOffset;
	float yOffset;

	float deltaX;
	float deltaY;


public:

	Line2D(unsigned int _lineWidth, int _shaderType, GLuint _shaderID);
	Line2D(float _p1x, float _p1y, float _p2x, float _p2y, unsigned int _lineWidth, int _shaderType, GLuint _shaderID);
	Line2D(std::vector<float> _points, unsigned int _lineWidth, int _shaderType, GLuint _shaderID);
	Line2D(std::vector<float>* _points, unsigned int _lineWidth, int _shaderType, GLuint _shaderID);
	~Line2D();

	void WindowUpdate(int _width, int _height);

	void AddVector(float _x, float _y);
	void AddPoint(float _x, float _y);
	void AddPoints(std::vector<float> _points);

	void DeleteSegment(unsigned int _segmentIndex);

	void SetLineWidth(float _lineWidth);

	void SetDeltaOffset(float _xOffset, float _yOffset);

	void SetOffset(float _xOffset, float _yOffset);

	float GetOffsetX();
	float GetOffsetY();

	int NumberOfSegments();

	void Render();


};
