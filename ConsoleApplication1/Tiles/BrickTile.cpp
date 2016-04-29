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

	std::vector<std::vector<WORD>> t(4, std::vector<WORD>(4, BACKGROUND_RED | BACKGROUND_GREEN));

	World::paintAt(*world, t, getXScaled(), getYScaled());
}
