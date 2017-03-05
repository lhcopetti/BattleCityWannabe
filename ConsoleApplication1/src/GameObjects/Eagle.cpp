#include "BattleCityClone.h"
#include "GameObjects\Eagle.h"
#include "Collision\Collidable.h"
#include "World.h"

using namespace GameObjects;


Eagle::Eagle(World* world, int x, int y) : GameObject(world, x, y, GameObjectType::EAGLE, EAGLE_HEIGHT, EAGLE_WIDTH)
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


 void Eagle::collide(Collidable* collidable)
{
	collidable->collideWith(this);
}


 void Eagle::collideWith(GameObjects::Eagle* eagle)
{
	/* What? Great design! */
}


 void Eagle::collideWith(GameObjects::Tank* tank)
{
	_alive = false;
}


 void Eagle::collideWith(GameObjects::Missile* missile)
{
	_alive = false;
}