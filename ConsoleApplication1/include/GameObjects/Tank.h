#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "GameObjects\Missile.h"
#include "Notify\GameObjectDied.h"
#include <Windows.h>

class World;

#define TANK_HEIGHT 3
#define TANK_WIDTH 3

namespace GameObjects
{

	class Tank : public GameObjects::GameObject, public InputListener, public Notify::GameObjectDied
	{

	private:
		Direction cDirection;
		String cDirectionSprite[3];
		std::vector<std::vector<WORD>> _tankColor;

		Missile *missile;
		bool _isPlayer;

		std::vector<String> getSpriteDirection() const;
		bool isTileWalkable(int x, int y) const;

	public:

		Tank(World* world, int x, int y, std::vector<std::vector<WORD>> tankColor, bool _isPlayer = false);

		void update();
		void paint(World* matrix) const;

		void keyPressed(int ch);
		bool shoot();

		bool moveDown();
		bool moveUp();
		bool moveLeft();
		bool moveRight();

		bool isPlayer() const { return _isPlayer; };

		void onGameObjectDeath(GameObjects::GameObject* gO);


		virtual void collide(Collidable* collidable);

		virtual void collideWith(GameObjects::Eagle* eagle);
		virtual void collideWith(GameObjects::Tank* tank);
		virtual void collideWith(GameObjects::Missile* missile);
	};
}
