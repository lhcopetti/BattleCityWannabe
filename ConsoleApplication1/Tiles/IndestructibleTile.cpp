#include "IndestructibleTile.h"
#include "../World.h"

using namespace Tiles;

IndestructibleTile::IndestructibleTile(int x, int y) : Tile(x, y, false, true, false)
{
}

void IndestructibleTile::paint(World* world) const
{
	std::vector<String> test
	{ "\xDB\xDB\xDB\xDB",
		"\xDB\xDB\xDB\xDB",
		"\xDB\xDB\xDB\xDB",
		"\xDB\xDB\xDB\xDB" };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
