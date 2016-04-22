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
	if (!_alive)
		return;

	if (countdown > 0)
	{
		countdown--;
		if (countdown == 0)
		{
			_alive = false;
			return;
		}
	}

	switch (cDirection)
	{
	case UP:
		yPos -= 1;
		break;
	case DOWN:
		yPos += 1;
		break;
	case LEFT:
		xPos -= 1;
		break;
	case RIGHT:
		xPos += 1;
		break;
	}

	if (xPos < 0 || xPos >= world->getWidth() || yPos < 0 || yPos >= world->getHeight())
		_alive = false;
}