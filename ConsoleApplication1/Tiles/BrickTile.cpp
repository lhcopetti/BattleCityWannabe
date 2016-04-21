#include "BrickTile.h"
#include "../World.h"

using namespace Tiles;

BrickTile::BrickTile(int x, int y) : Tile(x, y)
{
}

void BrickTile::paint(World* world) const
{
	std::vector<String> test
		{	"____",
			"|&&|",
			"|&&|",
			"____" };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
