#pragma once

#include <vector>
#include "BattleCityClone.h"
#include "Collision\Collidable.h"

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


	class GameObject : public Collidable
	{
	private:
		GameObjectType _type;

	protected:
		int xPos;
		int yPos;

		int _height;
		int _width;

		bool _alive = true;
		World* world;

	public:
		GameObject(World* world, int xPos, int yPos, GameObjectType type, int height, int width);

		int getX() const;
		int getY() const;

		int height() const { return _height; };
		int width() const { return _width; };

		bool isAlive() const;
		GameObjectType getType() const;

		virtual void update() = 0;
		virtual void paint(World* context) const = 0;

		virtual void collide(Collidable* collidable)= 0;

		virtual void collideWith(GameObjects::Eagle* eagle) = 0;
		virtual void collideWith(GameObjects::Tank* tank) = 0;
		virtual void collideWith(GameObjects::Missile* missile) = 0;
	};
}