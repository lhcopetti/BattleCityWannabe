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

Tank::Tank(World* world, int x, int y) : GameObject(world, x, y)
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
	yPos--;
	cDirection = UP;
}

void Tank::moveDown()
{
	yPos++;
	cDirection = DOWN;
}

void Tank::moveLeft()
{
	xPos--;
	cDirection = LEFT;
}

void Tank::moveRight()
{
	xPos++;
	cDirection = RIGHT;
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