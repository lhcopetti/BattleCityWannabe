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
		bool _isWall;
		bool _destroyed;
		bool _isDestructible;

	public:
		Tile(int x, int y, bool walkable, bool isWall = false, bool isDestructible = true);
		virtual void paint(World* world) const = 0;
		int getX() const;
		int getY() const;

		bool isWalkable() const;
		bool isWall() const;
		bool isDestroyed () const { return _destroyed; };
		bool isDestructible() const { return _isDestructible; };

		int getXScaled() const;
		int getYScaled() const;

		void destroy();


		static Tile* createBlownUpTile(int x, int y);
	};

}
