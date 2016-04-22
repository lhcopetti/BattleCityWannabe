#pragma once
#include "GameObjects\GameObject.h"

namespace Notify
{
	class GameObjectDied
	{
	public:
		virtual void onGameObjectDeath(GameObjects::GameObject* gO) = 0;
	};
}