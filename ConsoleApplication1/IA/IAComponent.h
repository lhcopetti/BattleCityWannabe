#pragma once

#include "GameObjects\Tank.h"

namespace IA
{
	class IAComponent
	{

	private:
		GameObjects::Tank* _tank;

	public:
		IAComponent(GameObjects::Tank* tank) { _tank = tank; };
		GameObjects::Tank* getTank() const { return _tank; };
		virtual void update() = 0;
	};
}