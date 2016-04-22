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
//		yPos = (yPos - 1) % world->getHeight();
		yPos = yPos - 1 < 0 ? world->getHeight() - (yPos - 1) : yPos - 1;
		break;
	case DOWN: 
		yPos = (yPos + 1) % world->getHeight();
		break;
	case LEFT:
//		xPos = (xPos - 1) % world->getWidth();
		xPos = xPos - 1 < 0 ? world->getWidth() - (xPos - 1) : xPos - 1;
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