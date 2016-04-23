#pragma once
#include "Tiles\Tile.h"

class World;


namespace Tiles
{
	class BlownUpTile : public Tile
	{

	public:
		BlownUpTile(int x, int y);
		void paint(World* world) const;
	};
}