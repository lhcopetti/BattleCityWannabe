#pragma once

#include "../GameObject.h"
#include "../Tank.h"
#include "../World.h"

namespace UnitCommand
{

	class UnitCommand
	{
	

	public:
		Tank *tank;

		UnitCommand(Tank* tank);

		virtual void execute(World* context) = 0;
	};

	class GoLeftCommand : public UnitCommand
	{

	public:
		GoLeftCommand(Tank* tank);

		void GoLeftCommand::execute(World* context);
	};

	class GoRightCommand : public UnitCommand
	{
	public:
		GoRightCommand(Tank* tank);

		void GoRightCommand::execute(World* context);
	};

	class GoUpCommand : public UnitCommand
	{
	public:
		GoUpCommand(Tank* tank);

		void GoUpCommand::execute(World* context);
	};

	class GoDownCommand : public UnitCommand
	{
	public:
		GoDownCommand(Tank* tank);

		void GoDownCommand::execute(World* context);
	};


	class ShootCommand : public UnitCommand
	{
	public:
		ShootCommand(Tank* tank);

		void ShootCommand::execute(World* context);
	};
}