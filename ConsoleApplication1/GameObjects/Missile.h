#pragma once

#include "GameObjects\GameObject.h"

class World;

namespace GameObjects
{
	class Missile : public GameObject
	{

	private:
		Direction cDirection;


	public:

		virtual void onMoveDown() = 0;
		virtual void onMoveUp() = 0;
		virtual void onMoveLeft() = 0;
		virtual void onMoveRight() = 0;

		virtual void paint(World* context) const;

	};
}