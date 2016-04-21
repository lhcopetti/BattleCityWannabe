#pragma once

#include "../BattleCityClone.h"
#include "Tile.h"

namespace Tiles
{

	class TileMap
	{

	private:
		Tile*** _tiles;
		int _height;
		int _width;

		TileMap();

	public:
		TileMap(String fileName);
		~TileMap();

		int height();
		int width();
		Tiles::Tile*** getTiles();
	};

}