#pragma once
#include "GameObject.h"
#include "InputListener.h"

class World;

class Tank : public Game::GameObject, public InputListener
{
#define TANK_HEIGHT 2
#define TANK_WIDTH 2

	enum Direction { LEFT, RIGHT, UP, DOWN };

private:
	Direction cDirection;
	String cDirectionSprite[3];

	std::vector<String> getSpriteDirection() const;

public:

	Tank(int x, int y);

	void Tank::paint(World* matrix) const;

	void Tank::keyPressed(int ch);

	void Tank::shoot();

	virtual void onMoveDown();
	virtual void onMoveUp();
	virtual void onMoveLeft();
	virtual void onMoveRight();

};