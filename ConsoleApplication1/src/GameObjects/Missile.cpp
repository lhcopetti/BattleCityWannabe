#include "BattleCityClone.h"
#include "World.h"
#include "GameObjects/Missile.h"
#include "GameObjects/Tank.h"

using namespace GameObjects;


Missile::Missile(World* world, int x, int y, Direction direction, Tank* owner) : GameObject(world, x, y, GameObjectType::MISSILE, MISSILE_HEIGHT, MISSILE_WIDTH)
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

	_tankOwner = owner;
}

void Missile::paint(World* world) const
{
	World::paintAt(*world, std::vector<String> { sprite }, yPos, xPos);

	World::paintAt(*world, std::vector<std::vector<WORD>>{ {FOREGROUND_RED} }, yPos, xPos);
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

void Missile::onTile(Tiles::Tile* tile)
{
	if (tile->isWall())
	{
		_alive = false;
		if (tile->isDestructible())
			tile->destroy();
	}
}

void Missile::collide(Collidable* collidable)
{
	collidable->collideWith((Missile*)this);
}

void Missile::collideWith(GameObjects::Eagle* eagle)
{
	_alive = false;
}


void Missile::collideWith(GameObjects::Tank* tank)
{
	//if (_tankOwner)
		if (tank->isPlayer() != _tankOwner->isPlayer())
			_alive = false;
}

void Missile::collideWith(GameObjects::Missile* missile)
{
	_alive = false;
}
