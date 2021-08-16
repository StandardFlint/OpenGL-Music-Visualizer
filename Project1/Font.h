
#ifndef Font_h
#define Font_h

#include <string>
#include <vector>
#include <fstream>
#include "lodepng.h"
#include <iostream>
#include "TextureBufferObject.h"


class Font{

private:

	std::vector<unsigned char> fontData;
	TextureBufferObject* fontTexture;
	unsigned int width;
	unsigned int height;
	int maxID;
	int size;
	int baseSize;
	struct charInfo {
		int charID;
		int xPos;
		int yPos;
		int width;
		int height;
		int xOffset;
		int yOffset;
		int xAdvance;
		int page;
		int chnl;
	};
	std::vector<charInfo> fontInfo;
	std::vector<charInfo*> charPointers;
	
	void SetInfo(const std::string _fontInfo);

public:

	Font(const std::string _fontAtlas, const std::string _fontInfo);
	~Font();

	charInfo* GetCharInfo(int _character);

	TextureBufferObject* GetFontTexture();
	unsigned char GetTexture(int _index);

	int GetTextureWidth();
	int GetTextureHeight();
	int GetSize();
	int GetBaseSize();


};
#endif