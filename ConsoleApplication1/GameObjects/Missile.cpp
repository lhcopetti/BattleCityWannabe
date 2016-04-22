#include "BattleCityClone.h"
#include "Missile.h"
#include "World.h"

using namespace GameObjects;


Missile::Missile(World* world, int x, int y, Direction direction) : GameObject(world, x, y)
{
	cDirection = direction;

	switch (cDirection)
	{
	case UP:
		sprite = "^";
		break;
	case LEFT:
		sprite = "<";
		break;
	case RIGHT:
		sprite = ">";
		break;
	case DOWN:
		sprite = "v";
		break;
	}
}

void Missile::paint(World* world) const
{
	World::paintAt(*world, std::vector<String> { sprite }, yPos, xPos);
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

void Missile::update()
{
	switch (cDirection)
	{
	case UP:
		yPos = (yPos - 1) % world->getHeight();
		break;
	case DOWN: 
		yPos = (yPos + 1) % world->getHeight();
		break;
	case LEFT:
		xPos = (xPos - 1) % world->getWidth();
		break;
	case RIGHT:
		xPos = (xPos + 1) % world->getWidth();
		break;
	}

	if (countdown > 0)
	{
		countdown--;
		if (countdown == 0)
			_alive = false;
	}
}