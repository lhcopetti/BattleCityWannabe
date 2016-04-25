#include "GameObject.h"
#include "Console\Console.h"

using namespace GameObjects;

GameObject::GameObject(World* w, int x, int y, GameObjectType type, int height, int width)
{
	this->world = w;
	this->xPos = x;
	this->yPos = y;
	this->_type = type;
	_height = height;
	_width = width;
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

GameObjectType GameObject::getType() const
{
	return _type;
}