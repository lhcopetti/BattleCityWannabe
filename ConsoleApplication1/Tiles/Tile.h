#pragma once

#define TILE_WIDTH 4
#define TILE_HEIGHT 4

class World;

namespace Tiles
{

	class Tile
	{
	protected:

		int _x;
		int _y;
		bool _walkable;

	public:
		Tile(int x, int y, bool walkable);
		virtual void paint(World* world) const = 0;
		int getX() const;
		int getY() const;
		bool isWalkable() const;

		int getXScaled() const;
		int getYScaled() const;
	};

}
