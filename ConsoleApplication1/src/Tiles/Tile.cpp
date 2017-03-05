
#include "Tiles/Tile.h"
#include "Tiles/BlownUpTile.h"

using namespace Tiles;

Tile::Tile(int x, int y, bool walkable, bool isWall, bool isDestructible)
{
	_x = x;
	_y = y;
	_walkable = walkable;
	_destroyed = false;
	_isWall = isWall;
	_isDestructible = isDestructible;
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

bool Tile::isWall() const
{
	return _isWall;
}

void Tile::destroy()
{
	_destroyed = true;
	_isWall = false;
}

Tile* Tile::createBlownUpTile(int x, int y)
{
	return new Tiles::BlownUpTile(x, y);
}
