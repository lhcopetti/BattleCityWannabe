#pragma once

#include "GameObjects\GameObject.h"
#include "GameObjects\Tank.h"

using namespace GameObjects;

namespace UnitCommand
{

	class UnitCommand
	{
	

	public:
		Tank *tank;

		UnitCommand(Tank* tank);

		virtual void execute() = 0;
	};

	class GoLeftCommand : public UnitCommand
	{

	public:
		GoLeftCommand(Tank* tank);

		void GoLeftCommand::execute();
	};

	class GoRightCommand : public UnitCommand
	{
	public:
		GoRightCommand(Tank* tank);

		void GoRightCommand::execute();
	};

	class GoUpCommand : public UnitCommand
	{
	public:
		GoUpCommand(Tank* tank);

		void GoUpCommand::execute();
	};

	class GoDownCommand : public UnitCommand
	{
	public:
		GoDownCommand(Tank* tank);

		void GoDownCommand::execute();
	};


	class ShootCommand : public UnitCommand
	{
	public:
		ShootCommand(Tank* tank);

		void ShootCommand::execute();
	};
}