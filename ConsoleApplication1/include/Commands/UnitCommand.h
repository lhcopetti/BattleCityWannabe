#pragma once

#include "GameObjects\GameObject.h"
#include "GameObjects\Tank.h"

using namespace GameObjects;

namespace UnitCommand
{

	class UnitCommand
	{

	protected:
		Tank *_tank;

	public:
		UnitCommand(Tank* tank) { _tank = tank; };

		virtual bool execute() = 0;
	};

	class GoLeftCommand : public UnitCommand
	{

	public:
		GoLeftCommand(Tank* tank) : UnitCommand(tank) {};

		bool execute();
	};

	class GoRightCommand : public UnitCommand
	{
	public:
		GoRightCommand(Tank* tank) : UnitCommand(tank) {};

		bool execute();
	};

	class GoUpCommand : public UnitCommand
	{
	public:
		GoUpCommand(Tank* tank) : UnitCommand(tank) {};

		bool execute();
	};

	class GoDownCommand : public UnitCommand
	{
	public:
		GoDownCommand(Tank* tank) : UnitCommand(tank) {};

		bool execute();
	};


	class ShootCommand : public UnitCommand
	{
	public:
		ShootCommand(Tank* tank) : UnitCommand(tank) {};

		bool execute();
	};
}
