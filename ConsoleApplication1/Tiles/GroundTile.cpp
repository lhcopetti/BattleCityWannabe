#include "GroundTile.h"
#include "../BattleCityClone.h"
#include <vector>
#include "../World.h"

using namespace Tiles;

GroundTile::GroundTile(int x, int y) : Tile(x, y, true)
{
}


void GroundTile::paint(World* world) const
{
	std::vector<String> test
						   {"....", 
							"....",
							"....",
							"...."};

	World::paintAt(*world, test, getXScaled(), getYScaled());

	std::vector<std::vector<WORD>> t(4, std::vector<WORD>(4, BACKGROUND_GREEN | FOREGROUND_INTENSITY));

	World::paintAt(*world, t, getXScaled(), getYScaled());

}
