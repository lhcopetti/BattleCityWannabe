#pragma once

#include "GameObjects\GameObject.h"
#include "Tiles\Tile.h"

class World;

#define MISSILE_HEIGHT 1
#define MISSILE_WIDTH 1

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

		void onTile(Tiles::Tile* tile);

		void update();

		virtual void collide(Collidable* collidable);

		virtual void collideWith(GameObjects::Eagle* eagle);
		virtual void collideWith(GameObjects::Tank* tank);
		virtual void collideWith(GameObjects::Missile* missile);
	};
}