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

void GameObject::moveUp()
{
	if (yPos > 0)
		yPos--;

	onMoveUp();
}

void GameObject::moveDown()
{
	yPos++;

	onMoveDown();
}

void GameObject::moveLeft()
{
	xPos--;

	onMoveLeft();
}

void GameObject::moveRight()
{
	xPos++;

	onMoveRight();
}

bool GameObject::isAlive() const
{
	return _alive;
}
