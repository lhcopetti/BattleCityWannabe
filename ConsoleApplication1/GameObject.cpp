#include "GameObject.h"
#include "Console\Console.h"

using namespace Game;

GameObject::GameObject(int x, int y)
{
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
