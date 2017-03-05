#pragma once
#include "Tile.h"

class World;

namespace Tiles
{
	class BrickTile : public Tile
	{

	public:
		BrickTile(int x, int y);
		void paint(World* world) const;
	};
}
