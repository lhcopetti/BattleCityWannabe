#include "Tank.h"
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

Tank::Tank(World* world, int x, int y) : GameObject(world, x, y, GameObjectType::TANK)
{
	cDirection = UP;
	missile = NULL;
}

void Tank::paint(World* context) const
{
	std::vector<String> spriteDirection = getSpriteDirection();

	World::paintAt(*context, spriteDirection, yPos, xPos);
}

void Tank::keyPressed(int ch)
{
	std::cout << "Some key has been pressed: " << ch << std::endl;
}

void Tank::shoot()
{
	if (missile == NULL)
	{
		missile = new Missile(world, xPos, yPos, cDirection);
		world->addGameObject(missile, this);
		std::cout << "Tank is shooting crazy" << std::endl;
	}
}

void Tank::moveUp()
{
	if (!world->isValidCoordinate(xPos, yPos - 1))
		return;

	for (int i = 0; i < TANK_WIDTH; i++)
		if (!isTileWalkable(xPos + i, yPos - 1))
			return;

	yPos--;
	cDirection = UP;
}

void Tank::moveDown()
{
	if (!world->isValidCoordinate(xPos, yPos + 1))
		return;

	for (int i = 0; i < TANK_WIDTH; i++)
		/* TANK_HEIGHT -1 because yPos already points to one of the tank's square. */
		if (!isTileWalkable(xPos + i, yPos + (TANK_HEIGHT - 1) + 1))
			return;

	yPos++;
	cDirection = DOWN;
}

void Tank::moveLeft()
{
	if (!world->isValidCoordinate(xPos - 1, yPos))
		return;

	for (int i = 0; i < TANK_HEIGHT; i++)
		if (!isTileWalkable(xPos - 1, yPos + i))
			return;

	xPos--;
	cDirection = LEFT;
}

void Tank::moveRight()
{
	if (!world->isValidCoordinate(xPos + 1, yPos))
		return;

	for (int i = 0; i < TANK_HEIGHT; i++)
		/* TANK_HEIGHT -1 because yPos already points to one of the tank's square. */
		if (!isTileWalkable(xPos + (TANK_WIDTH - 1) + 1, yPos + i))
			return;

	xPos++;
	cDirection = RIGHT;
}

bool Tank::isTileWalkable(int x, int y) const
{
	Tiles::Tile* tile = world->getTileFromCoordinate(y, x);

	return tile->isWalkable();
}

std::vector<String> Tank::getSpriteDirection() const
{
	std::vector<String> vec{ "@@", "@@" };
	return vec;
}

void Tank::update()
{
}

void Tank::onGameObjectDeath(GameObjects::GameObject* gO)
{
	delete missile;
	missile = NULL;
	std::cout << "Shots fired. It was not pretty!!!" << std::endl;
}