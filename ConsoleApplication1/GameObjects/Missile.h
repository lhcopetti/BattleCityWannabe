#pragma once

#include "GameObjects\GameObject.h"

class World;

namespace GameObjects
{
	class Missile : public GameObject
	{

	private:
		Direction cDirection;
		String sprite;
		int countdown = 50;

	public:
		Missile(World* world, int x, int y, Direction direction);

		virtual void onMoveDown();
		virtual void onMoveUp();
		virtual void onMoveLeft();
		virtual void onMoveRight();

		virtual void paint(World* context) const;

		void update();

	};
}