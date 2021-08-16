
#ifndef Text_h
#define Text_h

#include <string>
#include "ScreenObject.hpp"
#include "Font.h"



class Text : public ScreenObject{

private:

	std::string text;
	float size;
	float baseFontSize;


	float xOriginal;
	float yOriginal;

	float xInitial;
	float yInitial;

	Font* font;

	std::vector<float> textVerts;
	std::vector<float> textUVs;

	std::vector<unsigned int> indices;


	//float* positionData;


	float currentX;
	float currentY;

	int atlasWidth;
	int atlasHeight;

	int windowWidth;
	int windowHeight;

	int refWidth;
	int refHeight;

	int lines;
	float lineHeight;

	int baseSize = 256;

	float textWidth;
	float textHeight;

	float xOffset;
	float yOffset;



	bool centered;

	//void CorrectPos();


public:

	Text(std::string _text, int size, float _xInitial, float _yInitial, Font* _font, GLuint _shaderID);
	~Text();

	void UpdateText(std::string _text);

	void InitVert();
	void InitTex();
	void InitIndices();

	void NewSize(int _size);
	void NewPosition(float _x, float _y);


	void UpdateTextVert(int _width, int _height);
	//void MakeSquare(int _width, int _height);


	void UpdateVertices();
	void UpdateUVs();

	void Center();
	void Uncenter();

	bool IsCentered();

	void Render();

};
#endif