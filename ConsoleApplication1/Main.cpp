
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
//#include "Tiles\TileParser.h"

using namespace std;

int main()
{
	Tiles::TileMap tileMap("defaultMap.txt");
	World gameWorld(&tileMap);
	Collision::CollisionDetector collisionDetector(&gameWorld);

	Tank* playerTank = new Tank(&gameWorld, 50, 10);
	Tank* iaTank = new Tank(&gameWorld, 10, 50);

	gameWorld.addGameObject(playerTank);
	gameWorld.addGameObject(iaTank);

	IA::PrettyDumbIA iA(iaTank);

	KeyboardManager keyManager;
	keyManager.startManager();

	while (true)
	{
		//if (keyManager.getPressedKey)
		//{
			//int keyPressed = _getch();
			////cout << "Key Pressed: " << keyPressed << endl;
			//if (224 == keyPressed)
			//	keyPressed = _getch();

			////cout << "Key Pressed: " << keyPressed << endl;

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
		default:
			break;
		}
		if (command)
		{
			command->execute();
			delete command;
			command = nullptr;
		}

		iA.update();

		gameWorld.update();
		gameWorld.paint();

		Sleep(17);
	}


	String ttt;
	cin >> ttt;
	return 0;
}
