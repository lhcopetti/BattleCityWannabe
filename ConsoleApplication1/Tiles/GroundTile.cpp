#include "GroundTile.h"
#include "../BattleCityClone.h"
#include <vector>
#include "../World.h"

using namespace Tiles;

GroundTile::GroundTile(int x, int y) : Tile(x, y)
{
}


void GroundTile::paint(World* world) const
{
	std::vector<String> test
						   {"____", 
							"____",
							"____",
							"____"};

	World::paintAt(*world, test, getXScaled(), getYScaled());

}
