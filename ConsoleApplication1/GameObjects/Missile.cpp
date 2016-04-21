#include "BattleCityClone.h"
#include "Missile.h"
#include "World.h"

using namespace GameObjects;


void Missile::paint(World* world) const
{
	std::vector<String> x{ "^" };

	World::paintAt(*world, x, xPos, yPos);
}

void Missile::onMoveUp()
{
	cDirection = UP;
}

void Missile::onMoveDown()
{
	cDirection = DOWN;
}

void Missile::onMoveLeft()
{
	cDirection = LEFT;
}

void Missile::onMoveRight()
{
	cDirection = RIGHT;
}