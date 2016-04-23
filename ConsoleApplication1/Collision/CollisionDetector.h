#pragma once

#include <vector>

#include "BattleCityClone.h"
#include "Tiles\TileMap.h"
#include "GameObjects\GameObject.h"

class World;

namespace Collision
{
	class CollisionDetector
	{
	private:
		World* _world;

	public:
		CollisionDetector(World* world);
		void update();
	};
}