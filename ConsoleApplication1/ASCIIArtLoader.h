#pragma once

#include "BattleCityClone.h"
#include <vector>

class ASCIIArtLoader
{
private:
	std::vector<String> _art;
	int _width;
	int _height;


public:
	ASCIIArtLoader(String _fileName);

	void showArt();

	static void loadFile(String fileName, std::vector<String>& art);

};
