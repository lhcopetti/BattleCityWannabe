#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "GameObjects\Missile.h"

class World;

#define TANK_HEIGHT 2
#define TANK_WIDTH 2

namespace GameObjects
{

	class Tank : public GameObjects::GameObject, public InputListener
	{

	private:
		Direction cDirection;
		String cDirectionSprite[3];

		Missile *missile;

		std::vector<String> getSpriteDirection() const;

	public:

		Tank(int x, int y);

		void update();
		void Tank::paint(World* matrix) const;

		void Tank::keyPressed(int ch);

		void Tank::shoot();

		virtual void onMoveDown();
		virtual void onMoveUp();
		virtual void onMoveLeft();
		virtual void onMoveRight();

	};
}