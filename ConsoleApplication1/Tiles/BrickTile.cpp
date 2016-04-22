#include "BrickTile.h"
#include "../World.h"

using namespace Tiles;

BrickTile::BrickTile(int x, int y) : Tile(x, y, false)
{
}

void BrickTile::paint(World* world) const
{
	std::vector<String> test
	{	"####",
		"####",
		"####",
		"####" };

	World::paintAt(*world, test, getXScaled(), getYScaled());
}
