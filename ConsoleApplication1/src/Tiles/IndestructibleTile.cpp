#include "Tiles/IndestructibleTile.h"
#include "World.h"

using namespace Tiles;

IndestructibleTile::IndestructibleTile(int x, int y) : Tile(x, y, false, true, false)
{
}

void IndestructibleTile::paint(World* world) const
{
	std::vector<String> test
	{ "\xC9\xCB\xCB\xBB",
		"\xCC\xCE\xCE\xB9",
		"\xCC\xCE\xCE\xB9",
		"\xC8\xCA\xCA\xBC" };

	World::paintAt(*world, test, getXScaled(), getYScaled());

//	std::vector<std::vector<WORD>> t(TILE_HEIGHT, std::vector<WORD>(TILE_WIDTH, COLOR_BACKGROUND | FOREGROUND_RED | FOREGROUND_GREEN));
	std::vector<std::vector<WORD>> t(4, std::vector<WORD>(4, BACKGROUND_RED | BACKGROUND_GREEN));

	World::paintAt(*world, t, getXScaled(), getYScaled());
}
