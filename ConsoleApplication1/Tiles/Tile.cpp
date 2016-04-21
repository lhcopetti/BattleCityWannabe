
#include "Tile.h"

using namespace Tiles;

Tile::Tile(int x, int y)
{
	_x = x;
	_y = y;
}

int Tile::getX() const
{
	return _x;
}

int Tile::getY() const
{
	return _y;
}

int Tile::getXScaled() const
{
	return _x * TILE_HEIGHT;
}

int Tile::getYScaled() const
{
	return _y * TILE_WIDTH;
}