#pragma once

#include "IA\IAComponent.h"

class World;

namespace IA
{
	class PrettyDumbIA : public IAComponent
	{

	private:
		enum StateMachine
		{
			MOVE = 0,
			SHOOT = 1,
			CHANGE_DIRECTION = 2
		};

		StateMachine _previousState;
		bool _previousResult;

		StateMachine _currentState;
		Direction cDirection;

	public:
		PrettyDumbIA(World* world, GameObjects::Tank* tank);
		void update();
	};
}