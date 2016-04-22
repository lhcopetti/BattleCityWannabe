#include "GameObject.h"
#include "Console\Console.h"

using namespace GameObjects;

GameObject::GameObject(World* w, int x, int y)
{
	this->world = w;
	this->xPos = x;
	this->yPos = y;
}

int GameObject::getX() const
{
	return xPos;
}

int GameObject::getY() const
{
	return yPos;
}

bool GameObject::isAlive() const
{
	return _alive;
}
