
#include "UnitCommand.h"
#include "../BattleCityClone.h"

namespace UnitCommand
{

	UnitCommand::UnitCommand(Tank *tank)
	{
		this->tank = tank;
	}

	GoLeftCommand::GoLeftCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoLeftCommand::GoLeftCommand::execute(World* context)
	{
		tank->moveLeft();
	}

	GoRightCommand::GoRightCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoRightCommand::execute(World* context)
	{
		tank->moveRight();
	}


	GoUpCommand::GoUpCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoUpCommand::execute(World* context)
	{
		tank->moveUp();
	}

	GoDownCommand::GoDownCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoDownCommand::execute(World* context)
	{
		tank->moveDown();
	}


	ShootCommand::ShootCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void ShootCommand::execute(World* context)
	{
		tank->shoot();
	}
}