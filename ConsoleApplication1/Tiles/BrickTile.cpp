#include "BrickTile.h"
#include "../World.h"

using namespace Tiles;

BrickTile::BrickTile(int x, int y) : Tile(x, y, false, true)
{
}

void BrickTile::paint(World* world) const
{
	std::vector<String> test
	{ "\xc9\xCD\xCD\xBB",
		"\xb2\xb2\xb2\xb2",
		"\xb2\xb2\xb2\xb2",
		"\xb2\xb2\xb2\xb2" };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
