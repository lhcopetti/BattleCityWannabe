#pragma once

//#include "AStar.h"
#include "GridCell.h"

class World;

namespace IA {

	class IAAdapter
	{
	private:
		World* _world;
		int** gridAStar;


	public:
		IAAdapter(World* world) { _world = world; };

		GridCell* computeStep(int startX, int startY, int endX, int endY);

		static bool isTankAllowedToWalk(World& world, int i, int j);

		static int** translateWorld(World& world, int startX, int startY, int endX, int endY);
	};
}