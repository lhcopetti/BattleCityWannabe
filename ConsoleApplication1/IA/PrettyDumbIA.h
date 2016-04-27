#pragma once

#include "IA\IAComponent.h"

class World;
class GridCell;

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


		int _shoot;
		StateMachine _previousState;
		bool _previousResult;

		StateMachine _currentState;
		Direction cDirection;
		void moveTank(GridCell& g);

	public:
		PrettyDumbIA(World* world, GameObjects::Tank* tank);


		void update();
	};
}