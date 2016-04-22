
#include "Tile.h"

using namespace Tiles;

Tile::Tile(int x, int y, bool walkable)
{
	_x = x;
	_y = y;
	_walkable = walkable;
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

bool Tile::isWalkable() const
{
	return _walkable;
}