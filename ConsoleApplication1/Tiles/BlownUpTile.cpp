#include "Tiles\BlownUpTile.h"


#include "BrickTile.h"
#include "../World.h"

using namespace Tiles;

BlownUpTile::BlownUpTile(int x, int y) : Tile(x, y, true, false)
{
}

void BlownUpTile::paint(World* world) const
{
	std::vector<String> test
	{ "....",
		".__.",
		"_.._",
		"...." };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
