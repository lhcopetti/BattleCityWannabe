
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

	while (true)
	{
		if (_kbhit())
		{
			int keyPressed = _getch();
			//cout << "Key Pressed: " << keyPressed << endl;
			if (224 == keyPressed)
				keyPressed = _getch();

			//cout << "Key Pressed: " << keyPressed << endl;

			UnitCommand::UnitCommand* command = NULL;

			switch (keyPressed)
			{
			case 72:
				command = new UnitCommand::GoUpCommand(playerTank);
				break;
			case 75:
				command = new UnitCommand::GoLeftCommand(playerTank);
				break;
			case 77:
				command = new UnitCommand::GoRightCommand(playerTank);
				break;
			case 80:
				command = new UnitCommand::GoDownCommand(playerTank);
				break;
			case 32:
				command = new UnitCommand::ShootCommand(playerTank);
			default:
				break;
			}

			if (command)
			{
				command->execute();
				delete command;
			}
		}

		iA.update();

		gameWorld.update();
		gameWorld.paint();

		Sleep(17);
	}
	//Sleep(10 * 1000);

	//DepWorld world(100, vector<unsigned short>(45));

	//std::vector<GameObject*> gameObjects;
	//std::vector<Tank*> tanks;

	//for (size_t i = 0; i < world.size(); i++)
	//	for (size_t j = 0; j < world[0].size(); j++)
	//		world[i][j] = BACKGROUND_GREEN;


	//Tank* playerTank = new Tank(10, 10);

	//gameObjects.push_back(playerTank);
	//std::string ss;
	//ss.resize(300);

	//while (true)
	//{

	//	if (_kbhit())
	//	{
	//		int keyPressed = _getch();
	//		if (224 == keyPressed)
	//			keyPressed = _getch();

	//		cout << "Key Pressed: " << keyPressed << endl;

	//		Command::UnitCommand* command = NULL;

	//		switch (keyPressed)
	//		{
	//		case 72:
	//			command = new Command::GoUpCommand(playerTank);
	//			break;
	//		case 75:
	//			command = new Command::GoLeftCommand(playerTank);
	//			break;
	//		case 77:
	//			command = new Command::GoRightCommand(playerTank);
	//			break;
	//		case 80:
	//			command = new Command::GoDownCommand(playerTank);
	//			break;
	//		case 32:
	//			command = new Command::ShootCommand(playerTank);
	//		default:
	//			break;
	//		}

	//		if (command)
	//		{
	//			command->execute(&world);
	//			delete command;
	//		}

	//		//			cout << "Teste" << endl;
	//	}
	//	/*update();

	//	draw();*/

	//	//clrscr(COLOR_BACKGROUND);
	//	for (size_t i = 0; i < world[0].size(); i++)
	//	{
	//		mostrar(0, i, BACKGROUND_WHITE |  FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN, "____________________________________________________________________________________________________");
	//		//mostrar(0, i, BACKGROUND_RED, "____________________________________________________________________________________________________");
	//		//mostrar(0, i, BACKGROUND_WHITE, "____________________________________________________________________________________________________");
	//	}
	//	//playerTank->paint(world);
	//	ss.clear();

	//	/*for (size_t i = 0; i < world.size(); i++)
	//		for (size_t j = 0; j < world[0].size(); j++)
	//			mostratexto(i, j, " ", world[i][j]);*/

	//	Sleep(500);
	//}



	String ttt;
	cin >> ttt;
	return 0;
}
