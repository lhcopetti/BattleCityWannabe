#include "IA\PrettyDumbIA.h"
#include "IA\IAAdapter.h"
#include "GameObjects\Tank.h"

#include "Commands\UnitCommand.h"
#include "World.h"

using namespace GameObjects;

IA::PrettyDumbIA::PrettyDumbIA(World* world, Tank* tank) : IAComponent(world, tank)
{
	_previousState = MOVE;
	_currentState = MOVE;
	cDirection = RIGHT;

}

void IA::PrettyDumbIA::update()
{
	IA::IAAdapter adapter(_world);

	GridCell* g = adapter.computeStep(_tank->getX(), _tank->getY(),25, 0);

	if (g)
	{
		int currentX = _tank->getX();
		int currentY = _tank->getY();

		UnitCommand::UnitCommand* command;
		if (currentX - 1 == g->x() && currentY == g->y())
			command = new UnitCommand::GoLeftCommand(_tank);
		else if (currentX + 1 == g->x() && currentY == g->y())
			command = new UnitCommand::GoRightCommand(_tank);
		else if (currentX == g->x() && currentY - 1 == g->y())
			command = new UnitCommand::GoUpCommand(_tank);
		else if (currentX == g->x() && currentY + 1 == g->y())
			command = new UnitCommand::GoDownCommand(_tank);
		else
			command = new UnitCommand::ShootCommand(_tank);

		command->execute();
		delete g;
		delete command;
	}


}