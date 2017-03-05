
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
#include "ASCIIArtLoader.h"
#include "ASCIIArt\ConsolePainter.h"

#include "World.h"
#include "AStar.h"

using namespace std;

void showEndGame(World& world)
{
	clrscr(BACKGROUND_BLUE | FOREGROUND_GREEN);

	//char * str = ;

	mostrar(0, 0, FOREGROUND_BLUE | FOREGROUND_RED, "Voce venceu o jogo. Parabens");
}

enum GameStateMachine
{
	MENU_INTRO,
	MAIN_GAME,
	CREDITS_SCREEN,
	SUCESS_SCREEN,
	FAIL_SCREEN,
	EXIT_GAME
};


void processMenuIntro(GameStateMachine& gameState, KeyboardManager& keyManager)
{
	KeyboardManager::Keys keyPressed = keyManager.getPressedKey();

	mostrar(0, 0, FOREGROUND_WHITE, "MENU_INTRO");

	if (keyPressed == KeyboardManager::Keys::KEY_SPACE)
		gameState = MAIN_GAME;
	else if (keyPressed == KeyboardManager::Keys::KEY_ESC)
		gameState = EXIT_GAME;

	Sleep(30);
}

void processCredits(GameStateMachine& state, KeyboardManager& keyManager)
{
	clrscr(COLOR_BACKGROUND);
	ASCIIArtLoader asc("ASCIIArt\\credits.txt");
	asc.showArt();
	
	while (true)
	{
		KeyboardManager::Keys keyPressed = keyManager.getPressedKey();
		if (keyPressed == KeyboardManager::Keys::KEY_SPACE)
		{
			state = MENU_INTRO;
			break;
		}
		else if (keyPressed == KeyboardManager::Keys::KEY_ESC)
		{
			state = EXIT_GAME;
			break;
		}
	}

	Sleep(30);
}

void processSuccess(GameStateMachine& state, KeyboardManager& keyManager)
{
	clrscr(COLOR_BACKGROUND);
	//mostrar(0, 0, FOREGROUND_WHITE, "On SUCESS SCREEN");
	ASCIIArtLoader asc("ASCIIArt\\won_game.txt");
	asc.showArt();

	KeyboardManager::Keys keyPressed = keyManager.getPressedKey();
	if (keyPressed == KeyboardManager::Keys::KEY_SPACE)
		state = CREDITS_SCREEN;

	Sleep(30);
}

void processFailScreen(GameStateMachine& state, KeyboardManager& keyManager)
{
	clrscr(COLOR_BACKGROUND);
	ASCIIArtLoader asc("ASCIIArt\\you_failed.txt");
	asc.showArt();

	while (true)
	{
		KeyboardManager::Keys keyPressed = keyManager.getPressedKey();
		if (keyPressed == KeyboardManager::Keys::KEY_SPACE || keyPressed == KeyboardManager::Keys::KEY_ESC)
			break;
		Sleep(15);
	}
	state = CREDITS_SCREEN;
}

void processMainGame(GameStateMachine& state, KeyboardManager& keyManager)
{
	Tiles::TileMap tileMap("defaultMap.txt");

	World gameWorld(&tileMap);
	Collision::CollisionDetector collisionDetector(&gameWorld);


	Tank* playerTank = gameWorld.getPlayerTank();

	UnitCommand::UnitCommand* command = NULL;

	while (true)
	{
		KeyboardManager::Keys keyPressed = keyManager.getPressedKey();

		switch (keyPressed)
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
			state = CREDITS_SCREEN;
			return;
		default:
			break;
		}

		if (command)
		{
			command->execute();
			delete command;
			command = nullptr;
		}

		gameWorld.update();
		gameWorld.paint();

		if (gameWorld.getGameIsFinished())
		{
			if (gameWorld.getPlayerWon())
				state = SUCESS_SCREEN;
			else
				state = FAIL_SCREEN;
			break;
		}

		Sleep(25);
	}
}


int main()
{
	GameStateMachine state = MENU_INTRO;

	KeyboardManager keyManager;
	keyManager.startManager();

	srand(time(nullptr));

	while (true)
	{
		GameStateMachine lastState = state;

		switch (state)
		{
		case MENU_INTRO:
			processMenuIntro(state, keyManager);
			break;
		case MAIN_GAME:
			processMainGame(state, keyManager);
			Sleep(1500);
			break;
		case CREDITS_SCREEN:
			processCredits(state, keyManager);
			break;
		case SUCESS_SCREEN:
			processSuccess(state, keyManager);
			break;
		case FAIL_SCREEN:
			processFailScreen(state, keyManager);
			break;
		case EXIT_GAME:
			exit(0);
			break;
		}
		if (lastState != state)
			Sleep(500);

		lastState = state;
	}


	keyManager.stopManager();

	return 0;
}
