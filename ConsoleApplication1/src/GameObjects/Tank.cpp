#include "GameObjects/Tank.h"
#include "Console\Console.h"
#include "InputListener.h"
#include "World.h"

//
//static const String spriteUP[] =
//{
//	"  ||",
//	"/*||*\\",
//	"|*||*|",
//	"|****|",
//	"\\@@@@/"
//};
//
//static const String spriteDOWN[] =
//{
//	"/@@@@\\",
//	"|****|",
//	"|*||*|",
//	"\\*||*/",
//	"  ||"
//};
//
//static const String spriteLEFT[] =
//{
//	"===/**\\.",
//	" /*****\\", 
//	" \\_@_@_/"
//};
//static const String spriteRIGHT[] =
//{
//	"./**\\===",
//	"/*****\\", 
//	"\\_@_@_/"
//};

using namespace GameObjects;

Tank::Tank(World* world, int x, int y, std::vector<std::vector<WORD>> colors, bool isPlayer) : GameObject(world, x, y, GameObjectType::TANK, TANK_HEIGHT, TANK_WIDTH)
{
	cDirection = UP;
	missile = NULL;
	_tankColor = colors;
	_isPlayer = isPlayer;
}

void Tank::paint(World* context) const
{
	std::vector<String> spriteDirection = getSpriteDirection();

	World::paintAt(*context, spriteDirection, yPos, xPos);

//	std::vector<std::vector<WORD>> colors(3, std::vector<WORD>(3, FOREGROUND_RED));

	World::paintAt(*context, _tankColor, yPos, xPos);
}

void Tank::keyPressed(int ch)
{
//	std::cout << "Some key has been pressed: " << ch << std::endl;
}

bool Tank::shoot()
{
	if (missile)
		/* Cannot shoot until the missile is destroyed */
		return false;

	int missileX = xPos;
	int missileY = yPos;

	switch (cDirection)
	{
	case UP:
		missileX++;
		break;
	case LEFT:
		missileY++;
		break;
	case DOWN:
		missileX++;
		missileY += TANK_HEIGHT - 1;
		break;
	case RIGHT:
		missileY++;
		missileX += TANK_WIDTH - 1;
	}

	missile = new Missile(world, missileX, missileY, cDirection, this);
	world->addGameObject(missile, this);
//	std::cout << "Tank is shooting crazy" << std::endl;
	return true;
}

bool Tank::moveUp()
{
	cDirection = UP;

	if (!world->isValidCoordinate(xPos, yPos - 1))
		return false;

	for (int i = 0; i < TANK_WIDTH; i++)
		if (!isTileWalkable(xPos + i, yPos - 1))
			return false;

	yPos--;
	return true;
}

bool Tank::moveDown()
{
	cDirection = DOWN;

	if (!world->isValidCoordinate(xPos, yPos + 1 + (TANK_HEIGHT - 1)))
		return false;

	for (int i = 0; i < TANK_WIDTH; i++)
		/* TANK_HEIGHT -1 because yPos already points to one of the tank's square. */
		if (!isTileWalkable(xPos + i, yPos + (TANK_HEIGHT - 1) + 1))
			return false;

	yPos++;
	return true;
}

bool Tank::moveLeft()
{
	cDirection = LEFT;

	if (!world->isValidCoordinate(xPos - 1, yPos))
		return false;

	for (int i = 0; i < TANK_HEIGHT; i++)
		if (!isTileWalkable(xPos - 1, yPos + i))
			return false;

	xPos--;
	return true;
}

bool Tank::moveRight()
{
	cDirection = RIGHT;

	if (!world->isValidCoordinate(xPos + (TANK_WIDTH - 1) + 1, yPos))
		return false;

	for (int i = 0; i < TANK_HEIGHT; i++)
		/* TANK_HEIGHT -1 because yPos already points to one of the tank's square. */
		if (!isTileWalkable(xPos + (TANK_WIDTH - 1) + 1, yPos + i))
			return false;

	xPos++;
	return true;
}

bool Tank::isTileWalkable(int x, int y) const
{
	Tiles::Tile* tile = world->getTileFromCoordinate(y, x);

	return tile->isWalkable();
}

std::vector<String> Tank::getSpriteDirection() const
{
	switch (cDirection)
	{
	case UP:
		return { "\xC9\xBA\xBB", "\xC7\xCD\xB6", "@@@" };
		break;
	case DOWN:
		return{  "@@@", "\xC7\xCD\xB6", "\xC8\xBA\xBC"};
		break;
	case LEFT:
		return{ "\xC9\x41@", "\xCD\xBA@", "\xC8\x41@" };
		break;
	case RIGHT:
		return{ "@A\xBB", "@\xBA\xCD", "@A\xBC"};
		break;
	}
}

void Tank::update()
{
}

void Tank::onGameObjectDeath(GameObjects::GameObject* gO)
{
	delete missile;
	missile = NULL;
//	std::cout << "Shots fired. It was not pretty!!!" << std::endl;
}

void Tank::collide(Collidable* collidable)
{
	collidable->collideWith(this);
}

void Tank::collideWith(GameObjects::Eagle* eagle)
{

}
void Tank::collideWith(GameObjects::Tank* tank)
{

}

void Tank::collideWith(GameObjects::Missile* missile)
{
	//if (missile->getOwner())
	if (isPlayer() != missile->getOwner()->isPlayer())
		_alive = false;
}
