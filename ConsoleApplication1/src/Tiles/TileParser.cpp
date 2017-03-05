#include "Tiles/TileParser.h"
#include "Tiles/BrickTile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/TileMap.h"

#include <fstream>
#include <iostream>

using namespace Tiles;

TileParser::TileParser(String fileName)
{
	this->fileName = fileName;
}

TileParser::~TileParser()
{

}

/*void TileParser::getTiles(TileMap& tileMap)
{
	std::ifstream inputFile(fileName);

	std::vector<String> map;

	_width = -1;
	String cLine;
	while (std::getline(inputFile, cLine))
	{
		if (_width == -1 || cLine.length() < _width)
			_width = cLine.length();
		map.push_back(cLine);
	}
	_height = map.size();

	std::cout << "The width is: " << _width << std::endl;
	std::cout << "The height is: " << _height << std::endl;

	tiles = new Tile**[_height];

	for (int i = 0; i < _height; i++)
		tiles[i] = new Tile*[_width];

	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
		{
			if (map[i][j] == '0')
				tiles[i][j] = new BrickTile();
			else if (map[i][j] == '1')
				tiles[i][j] = new GroundTile();
		}

	//for (int i = 0; i < )


	for (int i = 0; i < map.size(); i++)
		std::cout << map.at(i) << std::endl;


	return;
/*	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			tiles[i][j] = new Tiles::BrickTile();

	return tiles;
	*/
/*	int i = 0;
	while (std::getline(inputFile, cLine))
	{

		for (int j = 0; j < cLine.length(); j++)
		{
			if (cLine.at(j) == '0')
				std::cout << "Teste" << std::endl;
			//	tiles[i][j] = new Tiles::
				//std::cout << "0 was found!" << std::endl;
		}
	}

	*/
//}
