#include "BrickTile.h"
#include "../World.h"

using namespace Tiles;

BrickTile::BrickTile(int x, int y) : Tile(x, y, false, true)
{
}

void BrickTile::paint(World* world) const
{
	std::vector<String> test
	{ "_|__|",
		"__|_",
		"_|__|",
		"__|_" };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
