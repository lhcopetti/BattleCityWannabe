
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
#include <iostream>

#include "BattleCityClone.h"
#include "Console\Console.h"
#include "GameObjects\GameObject.h"
#include "GameObjects\Tank.h"
#include "Commands\UnitCommand.h"
#include "Tiles\TileMap.h"
#include "IA\PrettyDumbIA.h"
#include "KeyboardManager.h"

#include "World.h"
#include "AStar.h"

using namespace std;

int main()
{
	bool exit = false;

	Tiles::TileMap tileMap("defaultMap.txt");
	World gameWorld(&tileMap);
	Collision::CollisionDetector collisionDetector(&gameWorld);

	KeyboardManager keyManager;
	keyManager.startManager();

	Tank* playerTank = gameWorld.getPlayerTank();

	bool toggle = false;

	while (true)
	{

		UnitCommand::UnitCommand* command = NULL;

		switch (keyManager.getPressedKey())
		{
		case KeyboardManager::Keys::KEY_UP_ARROW:
			command = new UnitCommand::GoUpCommand(playerTank);
			break;
		case KeyboardManager::Keys::KEY_LEFT_ARROW:
			command = new UnitCommand::GoLeftCommand(playerTank);
			break;
		case KeyboardManager::Keys::KEY_RIGHT_ARROW:
			command = new UnitCommand::GoRightCommand(playerTank);
			break;
		case KeyboardManager::Keys::KEY_DOWN_ARROW:
			command = new UnitCommand::GoDownCommand(playerTank);
			break;
		case KeyboardManager::Keys::KEY_SPACE:
			command = new UnitCommand::ShootCommand(playerTank);
			break;
		case KeyboardManager::Keys::KEY_ESC:
			exit = true;
			break;
		default:
			break;
		}

		if (exit)
			break;

		if (command)
		{
			if ((toggle ^= 1))
				command->execute();
			delete command;
			command = nullptr;
		}

		gameWorld.update();
		gameWorld.paint();

		Sleep(17);
	}

	keyManager.stopManager();

	return 0;
}
