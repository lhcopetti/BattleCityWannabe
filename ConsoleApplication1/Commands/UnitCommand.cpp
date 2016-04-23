
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

	void GoLeftCommand::GoLeftCommand::execute()
	{
		tank->moveLeft();
	}

	GoRightCommand::GoRightCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoRightCommand::execute()
	{
		tank->moveRight();
	}


	GoUpCommand::GoUpCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoUpCommand::execute()
	{
		tank->moveUp();
	}

	GoDownCommand::GoDownCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void GoDownCommand::execute()
	{
		tank->moveDown();
	}


	ShootCommand::ShootCommand(Tank* tank) : UnitCommand(tank)
	{
	}

	void ShootCommand::execute()
	{
		tank->shoot();
	}
}