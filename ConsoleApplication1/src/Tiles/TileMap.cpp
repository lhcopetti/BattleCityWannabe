#include "Tiles/TileMap.h"

#include <fstream>
#include <iostream>
#include <string>
#include "Tiles/BrickTile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/IndestructibleTile.h"


Tiles::TileMap::TileMap(String fileName)
{
	std::ifstream inputFile(fileName);

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
			int mapValue = map[i][j] - '0';

			if (mapValue == TILE_BRICK)
				_tiles[i][j] = new BrickTile(i, j);
			else if (mapValue == TILE_INDESTRUCTIBLE)
				_tiles[i][j] = new IndestructibleTile(i, j);
			else /* if (mapValue == TILE_GROUND) */
				_tiles[i][j] = new GroundTile(i, j);
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
