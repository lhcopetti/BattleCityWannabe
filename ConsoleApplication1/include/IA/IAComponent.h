#pragma once

#include "GameObjects\Tank.h"

class World;

namespace IA
{
	class IAComponent
	{

	private:

	protected:
		GameObjects::Tank* _tank;
		World* _world;

	public:
		IAComponent(World* world, GameObjects::Tank* tank) { _tank = tank; _world = world; };
		GameObjects::Tank* getTank() const { return _tank; };
		virtual void update() = 0;
	};
}