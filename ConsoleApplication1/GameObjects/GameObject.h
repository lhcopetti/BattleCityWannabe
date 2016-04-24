#pragma once

#include <vector>
#include "BattleCityClone.h"

enum Direction { LEFT, RIGHT, UP, DOWN };

class World;

namespace GameObjects
{
	enum GameObjectType
	{
		TANK,
		MISSILE,
		EAGLE
	};


	class GameObject
	{
	private:
		GameObjectType _type;

	protected:
		int xPos;
		int yPos;
		bool _alive = true;
		World* world;

	public:
		GameObject(World* world, int xPos, int yPos, GameObjectType type);
		int getX() const;
		int getY() const;
		bool isAlive() const;
		GameObjectType getType() const;

		virtual void update() = 0;
		virtual void paint(World* context) const = 0;
	};
}