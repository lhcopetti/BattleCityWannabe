#pragma once
#include "GameObjects\GameObject.h"

#define EAGLE_HEIGHT 4
#define EAGLE_WIDTH 4

namespace GameObjects
{
	class Eagle : public GameObject
	{
		private:

		public:
			Eagle(World* world, int x, int y);

			virtual void paint(World* context) const;

			void update();

			virtual void collide(Collidable* collidable);

			virtual void collideWith(GameObjects::Eagle* eagle);
			virtual void collideWith(GameObjects::Tank* tank);
			virtual void collideWith(GameObjects::Missile* missile);
	};
}