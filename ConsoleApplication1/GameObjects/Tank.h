#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "GameObjects\Missile.h"
#include "Notify\GameObjectDied.h"

class World;

#define TANK_HEIGHT 2
#define TANK_WIDTH 2

namespace GameObjects
{

	class Tank : public GameObjects::GameObject, public InputListener, public Notify::GameObjectDied
	{

	private:
		Direction cDirection;
		String cDirectionSprite[3];

		Missile *missile;

		std::vector<String> getSpriteDirection() const;
		bool isTileWalkable(int x, int y) const;

	public:

		Tank(World* world, int x, int y);

		void update();
		void Tank::paint(World* matrix) const;

		void Tank::keyPressed(int ch);

		void Tank::shoot();

		void moveDown();
		void moveUp();
		void moveLeft();
		void moveRight();

		void onGameObjectDeath(GameObjects::GameObject* gO);
	};
}