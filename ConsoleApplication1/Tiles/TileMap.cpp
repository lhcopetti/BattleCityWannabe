#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <string>
#include "BrickTile.h"
#include "GroundTile.h"


Tiles::TileMap::TileMap(String fileName)
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

	_tiles = new Tiles::Tile**[_height];

	for (int i = 0; i < _height; i++)
		_tiles[i] = new Tiles::Tile*[_width];

	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
		{
			if (map[i][j] == '0')
				_tiles[i][j] = new GroundTile(i, j);
			else /* if (map[i][j] == '1') */
				_tiles[i][j] = new BrickTile(i, j);
		}
}

Tiles::TileMap::~TileMap()
{

}

Tiles::Tile*** Tiles::TileMap::getTiles()
{
	return _tiles;
}

int Tiles::TileMap::height()
{
	return _height;
}

int Tiles::TileMap::width()
{
	return _width;
}