#include "BattleCityClone.h"
#include "GameObjects\Eagle.h"
#include "World.h"

using namespace GameObjects;


Eagle::Eagle(World* world, int x, int y) : GameObject(world, x, y, GameObjectType::EAGLE)
{
}

void Eagle::paint(World* world) const
{
	std::vector<String> sprite 
		{
			"_/\\_", 
			"\\../", 
			".||.", 
			"\xBC  \xC8"
	};
	World::paintAt(*world, std::vector<String> { sprite }, yPos, xPos);
}


void Eagle::update()
{

}
