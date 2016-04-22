#pragma once

#include <vector>
#include "BattleCityClone.h"

enum Direction { LEFT, RIGHT, UP, DOWN };

class World;

namespace GameObjects
{

	class GameObject
	{

	protected:
		int xPos;
		int yPos;
		bool _alive = true;
		World* world;

	public:
		GameObject(World* world, int xPos, int yPos);
		int getX() const;
		int getY() const;
		bool isAlive() const;

		virtual void update() = 0;
		virtual void paint(World* context) const = 0;
	};
}