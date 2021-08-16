

#include "Text.h"


Text::Text(std::string _text, int _size, float _xInitial, float _yInitial, Font* _font, GLuint _shaderID) : ScreenObject(0, _shaderID, GL_TRIANGLES, _text.size()*6) {

	font = _font;
	text = _text;
	size = (float)_size / baseSize;

	windowWidth = 1000;
	windowHeight = 1000;
	refWidth = 1000;
	refHeight = 1000;
	atlasWidth = font->GetTextureWidth();
	atlasHeight = font->GetTextureHeight();\

	xOffset = 0;
	yOffset = 0;

	xOriginal = _xInitial;
	yOriginal = _yInitial;
	xInitial = _xInitial;
	yInitial = _yInitial;
	centered = false;

	baseFontSize = ((float)font->GetSize() / atlasHeight);

	lineHeight = baseFontSize * ((float)refHeight / windowHeight);

	InitVert();
	InitTex();
	InitIndices();


	AddVertexBuffer(&textVerts, 2, 0);
	AddVertexBuffer(&textUVs, 2, 0);
	SetTextureBuffer(font->GetFontTexture());
	SetIndexBuffer(&indices);


	SetObjectColor(1.0, 1.0, 1.0, 1.0);


}

Text::~Text() {

}



void Text::InitVert() {

	textVerts.clear();
	currentX = 0;
	currentY = 0;
	lines = 1;
	textWidth = 0;
	textHeight = -lineHeight;

	for (int i = 0; i < text.size(); i++) {

		if (text[i] == '\n') {

			currentY = lines * -lineHeight;
			textHeight -= lineHeight;
			currentX = 0;
			lines++;

		}
		else {

			float w = ((float)font->GetCharInfo(text[i])->width / atlasWidth) * ((float)refWidth/windowWidth);
			float h = ((float)font->GetCharInfo(text[i])->height / atlasHeight) * ((float)refHeight / windowHeight);

			float x = (((float)font->GetCharInfo(text[i])->xOffset / atlasWidth) * ((float)refWidth / windowWidth) + currentX);
			
			float y = (currentY - ((float)font->GetCharInfo(text[i])->yOffset / atlasHeight) * ((float)refHeight / windowHeight));

			
			float currentVerts[] = { x,     y,
									 x + w, y,
									 x,     y - h,
									 x + w, y - h };


			textVerts.insert(textVerts.end(), currentVerts, currentVerts + 8);

			currentX += ((float)font->GetCharInfo(text[i])->xAdvance / atlasWidth) * ((float)refWidth / windowWidth);

			if (currentX > textWidth) {
				textWidth = currentX;
			}

		}

	}

}



void Text::InitTex() {

	textUVs.clear();

	for (int i = 0; i < text.size(); i++) {

		if (text[i] != '\n') {

			float x = (float)font->GetCharInfo(text[i])->xPos / atlasWidth;
			float y = (float)font->GetCharInfo(text[i])->yPos / atlasHeight;

			float w = (float)font->GetCharInfo(text[i])->width / atlasWidth;
			float h = (float)font->GetCharInfo(text[i])->height / atlasHeight;


			float currentUVs[] = { x,     y,
								   x + w, y,
							       x,     y + h,
								   x + w, y + h };


			textUVs.insert(textUVs.end(), currentUVs, currentUVs + 8);

		}

	}

}


void Text::InitIndices() {

	indices.clear();

	for (int i = 0; i < text.size(); i++) {

		int offset = i * 4;

		unsigned int currentIndices[] = { static_cast<unsigned int>(0 + offset),
										  static_cast<unsigned int>(1 + offset),
										  static_cast<unsigned int>(2 + offset),

										  static_cast<unsigned int>(3 + offset),
										  static_cast<unsigned int>(2 + offset),
										  static_cast<unsigned int>(1 + offset) };


		indices.insert(indices.end(), currentIndices, currentIndices + 6);

	}

	if(GetIndexBuffer() != nullptr)
		GetIndexBuffer()->UpdateIndices(&indices);

}

void Text::UpdateText(std::string _text) {

	text = _text;
	SetVertexCount(_text.size() * 6);
	UpdateVertices();
	UpdateUVs();

}


void Text::NewSize(int _size) {

	size = (float)_size / baseSize;

}



void Text::NewPosition(float _x, float _y) {

	xOriginal = _x;
	yOriginal = _y;

}



void Text::UpdateTextVert(int _width, int _height) {

	lineHeight = baseFontSize * ((float)refHeight / _height);

	if (centered == false) {
		xOffset = 0;
		yOffset = 0;
		textHeight = lineHeight * lines;
	}
	else {
		textHeight = -lineHeight * lines;
		textWidth = (textWidth / ((float)refWidth / windowWidth)) * ((float)refWidth / _width);
		xOffset = (textWidth / 2);
		yOffset = (textHeight / 2);
	}

	windowWidth = _width;
	windowHeight = _height;
	UpdateVertices();

}







void Text::UpdateVertices() {

	InitVert();
	GetVertexBuffer(0)->UpdateVertices(&textVerts);
	InitIndices();

}


void Text::UpdateUVs() {

	InitTex();
	GetVertexBuffer(1)->UpdateVertices(&textUVs);

}




void Text::Center() { //costly, make sure to optimize

	if (centered == false) {
		centered = true;
		xOffset = (textWidth / 2);
		yOffset = (textHeight / 2);
	}

}


void Text::Uncenter() {

	if (centered == true) {
		centered = false;
		xOffset = 0;
		yOffset = 0;
	}

}


bool Text::IsCentered() {

	return centered;

}

void Text::Render() {

	GLint loc = glGetUniformLocation(GetShaderID(), "_scale");
	GLint loc2 = glGetUniformLocation(GetShaderID(), "_position");
	GLint loc3 = glGetUniformLocation(GetShaderID(), "_centerOffset");
	glUniform1f(loc, size);
	glUniform2f(loc2, xOriginal, yOriginal);
	glUniform2f(loc3, xOffset, yOffset);

	ScreenObject::Render();

}
