#pragma once
#include "Tile.h"

class World;

namespace Tiles
{
	class IndestructibleTile : public Tile
	{

	public:
		IndestructibleTile(int x, int y);
		void paint(World* world) const;
	};
}
