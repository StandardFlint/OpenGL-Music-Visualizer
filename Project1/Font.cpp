
#include "Font.h"



Font::Font(std::string _fontAtlas, std::string _fontInfo) {

	lodepng::decode(fontData, width, height, _fontAtlas);
	fontTexture = new TextureBufferObject(fontData.data(), fontData.size()*sizeof(char), GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE);
	maxID = 0;
	baseSize = 0;
	SetInfo(_fontInfo);

}


Font::~Font() {
	//delete fontTexture;  //NOTE: add back later when font object isnt destroyed
}


void Font::SetInfo(std::string _fontInfo) {

	std::ifstream fontFile(_fontInfo);
	std::string word;
	int charCount;

	fontFile.ignore(512, '=');
	fontFile.ignore(512, '=');
	fontFile >> size;

	//std::cout << size << std::endl;

	fontFile >> word;
	while (word.compare("common")) {
		fontFile >> word;
	}

	fontFile.ignore(512, '=');
	fontFile.ignore(512, '=');
	fontFile >> baseSize;

	//std::cout << baseSize << std::endl;

	fontFile >> word;
	while (word.compare("chars")) {
		fontFile >> word;
	}

	fontFile.ignore(512, '=');
	fontFile >> charCount;
	
	for (int i = 0; i < charCount; i++) {

		charInfo element;
		int current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.charID = current;
		if (current > maxID)
			maxID = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.xPos = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.yPos = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.width = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.height = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.xOffset = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.yOffset = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.xAdvance = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.page = current;

		fontFile.ignore(512, '=');
		fontFile >> current;
		element.chnl = current;

		fontInfo.push_back(element);

	}


	//Set Pointers to each character's information struct
	int counter = 0;
	for (int i = 0; i <= maxID; i++) {

		charPointers.push_back(nullptr);

		if (fontInfo[counter].charID == i) {
			charPointers[i] = &fontInfo[counter];
			counter++;
		}
	}

}


Font::charInfo* Font::GetCharInfo(int _character) {

	if (_character <= maxID)
		return charPointers[_character];
	else
		return nullptr;

}

TextureBufferObject* Font::GetFontTexture() {

	return fontTexture;

}


int Font::GetTextureWidth() {

	return width;

}


int Font::GetTextureHeight() {

	return height;

}

int Font::GetSize() {

	return size;

}

int Font::GetBaseSize() {

	return baseSize;

}


unsigned char Font::GetTexture(int _index) {
	return fontData[_index];
}