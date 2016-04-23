
#include "UnitCommand.h"
#include "../BattleCityClone.h"

namespace UnitCommand
{
	bool GoLeftCommand::GoLeftCommand::execute()
	{
		return _tank->moveLeft();
	}

	bool GoRightCommand::execute()
	{
		return _tank->moveRight();
	}

	bool GoUpCommand::execute()
	{
		return _tank->moveUp();
	}

	bool GoDownCommand::execute()
	{
		return _tank->moveDown();
	}

	bool ShootCommand::execute()
	{
		return _tank->shoot();
	}
}