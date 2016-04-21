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

Tank::Tank(int x, int y) : GameObject(x, y)
{
	cDirection = UP;
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
	std::cout << "Tank is shooting crazy" << std::endl;
}

void Tank::onMoveUp()
{
	cDirection = UP;
}

void Tank::onMoveDown()
{
	cDirection = DOWN;
}

void Tank::onMoveLeft()
{
	cDirection = LEFT;
}

void Tank::onMoveRight()
{
	cDirection = RIGHT;
}

std::vector<String> Tank::getSpriteDirection() const
{
	std::vector<String> vec{ "@@", "@@" };
	return vec;
	//switch (cDirection)
	//{
	//case UP:
	//	vec.push_back(spriteUP[0]);
	//	vec.push_back(spriteUP[1]);
	//	vec.push_back(spriteUP[2]);
	//	vec.push_back(spriteUP[3]);
	//	vec.push_back(spriteUP[4]);
	//	break;
	//case DOWN:
	//	vec.push_back(spriteDOWN[0]);
	//	vec.push_back(spriteDOWN[1]);
	//	vec.push_back(spriteDOWN[2]);
	//	vec.push_back(spriteDOWN[3]);
	//	vec.push_back(spriteDOWN[4]);
	//	break;
	//case LEFT:
	//	vec.push_back(spriteLEFT[0]);
	//	vec.push_back(spriteLEFT[1]);
	//	vec.push_back(spriteLEFT[2]);
	//	break;
	//case RIGHT:
	//	vec.push_back(spriteRIGHT[0]);
	//	vec.push_back(spriteRIGHT[1]);
	//	vec.push_back(spriteRIGHT[2]);
	//	break;
	//}

	//return vec;
}

void Tank::update()
{

}