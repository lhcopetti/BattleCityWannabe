#include "World.h"

#include "Tiles/BlownUpTile.h"
#include "Tiles/BrickTile.h"

using namespace Tiles;

BlownUpTile::BlownUpTile(int x, int y) : Tile(x, y, true, false)
{
}

void BlownUpTile::paint(World* world) const
{
	std::vector<String> test
	{ "@@@@",
		"@@@@",
		"@@@@",
		"@@@@" };

	World::paintAt(*world, test, getXScaled(), getYScaled());

	std::vector<std::vector<WORD>> t(4, std::vector<WORD>(4, BACKGROUND_GREEN | FOREGROUND_INTENSITY));

	World::paintAt(*world, t, getXScaled(), getYScaled());

}
