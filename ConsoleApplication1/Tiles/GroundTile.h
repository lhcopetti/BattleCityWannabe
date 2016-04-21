#pragma once
#include "Tile.h"

namespace Tiles
{
	class GroundTile : public Tile
	{

	public:
		GroundTile(int x, int y);
		void paint(World* world) const;
	};
}
