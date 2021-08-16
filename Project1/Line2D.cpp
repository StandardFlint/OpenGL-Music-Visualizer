#include "Line2D.h"

Line2D::Line2D(unsigned int _lineWidth, int _shaderType, GLuint _shaderID) : ScreenObject(_shaderType, _shaderID, GL_LINES, 0) {

	linePoints = new std::vector<float>;

	numberOfSegments = 0;

	lineWidth = _lineWidth;

	xOffset = 0.0;
	yOffset = 0.0;

	windowWidth = 1000;
	windowHeight = 1000;

	AddVertexBuffer(linePoints, 2, 0);

	SetObjectColor(1.0, 1.0, 1.0, 1.0);

}

Line2D::Line2D(float _p1x, float _p1y, float _p2x, float _p2y, unsigned int _lineWidth, int _shaderType, GLuint _shaderID) : ScreenObject(_shaderType, _shaderID, GL_LINES, 2) {

	linePoints = new std::vector<float>;

	linePoints->push_back(_p1x);
	linePoints->push_back(_p1y);
	linePoints->push_back(_p2x);
	linePoints->push_back(_p2y);

	numberOfSegments = 1;


	lineWidth = _lineWidth;

	xOffset = 0.0;
	yOffset = 0.0;

	windowWidth = 1000;
	windowHeight = 1000;


	AddVertexBuffer(linePoints, 2, 0);

	SetObjectColor(1.0, 1.0, 1.0, 1.0);


}

Line2D::Line2D(std::vector<float> _points, unsigned int _lineWidth, int _shaderType, GLuint _shaderID) : ScreenObject(_shaderType, _shaderID, GL_LINES, _points.size() / 2) {

	linePoints = new std::vector<float>;

	linePoints->insert(linePoints->end(), _points.begin(), _points.end());

	numberOfSegments = _points.size() / 4;

	lineWidth = _lineWidth;

	xOffset = 0.0;
	yOffset = 0.0;

	windowWidth = 1000;
	windowHeight = 1000;

	AddVertexBuffer(linePoints, 2, 0);

	SetObjectColor(1.0, 1.0, 1.0, 1.0);

}

Line2D::Line2D(std::vector<float>* _points, unsigned int _lineWidth, int _shaderType, GLuint _shaderID) : ScreenObject(_shaderType, _shaderID, GL_LINES, _points->size() / 2) {

	linePoints = _points;

	numberOfSegments = _points->size() / 4;


	lineWidth = _lineWidth;

	xOffset = 0.0;
	yOffset = 0.0;

	windowWidth = 1000;
	windowHeight = 1000;


	AddVertexBuffer(linePoints, 2, 0);

	SetObjectColor(1.0, 1.0, 1.0, 1.0);


}

Line2D::~Line2D() {


}



void Line2D::WindowUpdate(int _width, int _height) {

	windowWidth = _width;
	windowHeight = _height;

}


void Line2D::AddVector(float _x, float _y) {

	if (linePoints->size() > 2) {
		float lastX = (*linePoints)[linePoints->size() - 2];
		float lastY = (*linePoints)[linePoints->size() - 1];

		linePoints->push_back(lastX);
		linePoints->push_back(lastY);

		linePoints->push_back(lastX + _x);
		linePoints->push_back(lastY + _y);
	}
	else if (linePoints->size() == 2) {

		float lastX = linePoints->front();
		float lastY = linePoints->back();

		linePoints->push_back(lastX + _x);
		linePoints->push_back(lastY + _y);

		SetVertexCount(GetVertexCount() + 1);
		numberOfSegments++;
	}
	else {

		linePoints->push_back(_x);
		linePoints->push_back(_y);

		SetVertexCount(GetVertexCount() + 1);

	}


	if (VertexBufferSize() == 0) {

		AddVertexBuffer(linePoints, 2, 0);

	}
	else {

		GetVertexBuffer(0)->UpdateVertices(linePoints);

	}

}



void Line2D::AddPoint(float _x, float _y) {

	if (linePoints->size() > 2) {

		float lastX = (*linePoints)[linePoints->size() - 2];
		float lastY = (*linePoints)[linePoints->size() - 1];

		linePoints->push_back(lastX);
		linePoints->push_back(lastY);

		linePoints->push_back(_x);
		linePoints->push_back(_y);

		SetVertexCount(GetVertexCount() + 2);
		numberOfSegments++;

	}
	else if (linePoints->size() == 2) {

		linePoints->push_back(_x);
		linePoints->push_back(_y);

		SetVertexCount(GetVertexCount() + 1);
		numberOfSegments++;
	}
	else {

		linePoints->push_back(_x);
		linePoints->push_back(_y);

		SetVertexCount(GetVertexCount() + 1);

	}


	if (VertexBufferSize() == 0) {
		AddVertexBuffer(linePoints, 2, 0);
	}
	else {
		GetVertexBuffer(0)->UpdateVertices(linePoints);
	}

	

}

void Line2D::AddPoints(std::vector<float> _points) {

	if (linePoints->size() >= 2) {
		float lastX = (*linePoints)[linePoints->size() - 2];
		float lastY = (*linePoints)[linePoints->size() - 1];

		linePoints->push_back(lastX);
		linePoints->push_back(lastY);

		linePoints->insert(linePoints->end(), _points.begin(), _points.end());
	}
	else {
		linePoints->insert(linePoints->begin(), _points.begin(), _points.end());
	}


	if (VertexBufferSize() == 0) {

		AddVertexBuffer(linePoints, 2, 0);

	}
	else {

		GetVertexBuffer(0)->UpdateVertices(linePoints);

	}

	SetVertexCount(GetVertexCount() + (_points.size() / 2));

	numberOfSegments += _points.size() / 4;

}








void Line2D::DeleteSegment(unsigned int _segmentIndex) {

	if (_segmentIndex < numberOfSegments) {

		int vertexIndex = _segmentIndex * 4;

		linePoints->erase(linePoints->begin() + vertexIndex, linePoints->begin() + vertexIndex + 4);

		GetVertexBuffer(0)->UpdateVertices(linePoints);

		SetVertexCount(GetVertexCount() - 2);

		numberOfSegments--;

	}

}



int Line2D::NumberOfSegments() {

	return numberOfSegments;

}



void Line2D::SetLineWidth(float _lineWidth) {

	lineWidth = _lineWidth;

}




void Line2D::SetDeltaOffset (float _xOffset, float _yOffset) {

	deltaX = _xOffset;
	deltaY = _yOffset;

}


void Line2D::SetOffset(float _xOffset, float _yOffset) {

	xOffset = _xOffset;
	yOffset = _yOffset;

}



float Line2D::GetOffsetX() {

	return xOffset;

}


float Line2D::GetOffsetY() {

	return yOffset;

}




void Line2D::Render() {

    xOffset += deltaX;
    yOffset += deltaY;

	GLint loc = glGetUniformLocation(GetShaderID(), "_lineWidth");
	GLint loc2 = glGetUniformLocation(GetShaderID(), "_windowInfo");
	GLint loc3 = glGetUniformLocation(GetShaderID(), "_offset");

	glUniform1f(loc, lineWidth);
	glUniform2f(loc2, windowWidth, windowHeight);
	glUniform2f(loc3, xOffset, yOffset);

	ScreenObject::Render();

}
