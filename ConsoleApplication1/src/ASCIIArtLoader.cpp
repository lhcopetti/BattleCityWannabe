
#include "ASCIIArtLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Console\Console.h"

ASCIIArtLoader::ASCIIArtLoader(String fileName)
{
	loadFile(fileName, _art);
}

void ASCIIArtLoader::showArt()
{
	for (int i = 0; i < _art.size(); i++)
		mostrar(0, i, BACKGROUND_WHITE | FOREGROUND_GREEN, (char*)_art[i].c_str());
}

void ASCIIArtLoader::loadFile(String fileName, std::vector<String>& art)
{
	std::ifstream inputFile(fileName);

	String cLine;
	while (std::getline(inputFile, cLine))
	{
		art.push_back(cLine);
	}
}