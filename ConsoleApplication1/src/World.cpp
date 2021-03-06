#include "World.h"
#include "Console\Console.h"
#include "Tiles\TileMap.h"
#include "Tiles\Tile.h"
#include "GameObjects\Eagle.h"
#include "IA\PrettyDumbIA.h"
#include "IA\IAComponent.h"
#include "ASCIIArt\ConsolePainter.h"

#include <sstream>
#include <cassert>

using Time = std::chrono::high_resolution_clock;

World::World(Tiles::TileMap* tileMap)
{
	_tileMap = tileMap;
	_gameIsFinished = false;

	extractGameObjects(*_tileMap);

	_startTime = sClock_t::now();

	_painter = new ConsolePainter(getHeight(), getWidth());

	clear();
}

World::~World()
{
	delete _painter;
}

int World::getHeight() const
{
	return _tileMap->height() * TILE_HEIGHT;
}

int World::getWidth() const
{
	return _tileMap->width() * TILE_WIDTH;
}

void World::addGameObject(GameObjects::GameObject* go)
{
	addGameObject(go, NULL);
}

void World::addGameObject(GameObjects::GameObject* gO, Notify::GameObjectDied* gDied)
{
	_notifyObjects[gO] = gDied;
}

void World::clear()
{
	charWorld.clear();

	for (size_t i = 0; i < getHeight(); i++)
	{
		String str(getWidth() - 1, '_');
		charWorld.push_back(str);
	}

	for (int i = 0; i < getHeight(); i++)
	{
		_colors.push_back(std::vector<WORD>(getWidth(), COLOR_BACKGROUND | FOREGROUND_BLUE));
	}
}

void World::paint()
{
	for (int i = 0; i < _tileMap->height(); i++)
	{
		for (int j = 0; j < _tileMap->width(); j++)
		{
			assert(NULL != _tileMap->getTiles());
			Tiles::Tile* t = _tileMap->getTiles()[i][j];
			//			std::cout << "Running tile at: " << t->getX() << " and " << t->getY() << " Header Guard " << std::endl;
			_tileMap->getTiles()[i][j]->paint(this);
		}
	}

	for (std::map<GameObjects::GameObject*, Notify::GameObjectDied*>::iterator iter = _notifyObjects.begin(); iter != _notifyObjects.end(); ++iter)
	{
		iter->first->paint(this);
	}
	_painter->paint(charWorld, _colors);

	/*	for (int i = 0; i < getHeight(); i++)
			mostrar(0, i, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)charWorld[i].c_str());

		updateFooter();

		for (int i = 0; i < _footer.size(); i++)
			mostrar(0, getHeight() + i,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)_footer[i].c_str());

			*/
}

void World::updateFooter()
{
	_footer.clear();
	std::stringstream stream;
	stream << "Running Time: " << getElapsedSeconds();
	_footer.push_back(stream.str());

	std::stringstream sstream;
	sstream << "Tanks Remaining: " << getRemainingTanks();
	_footer.push_back(sstream.str());
}

void World::paintAt(World& world, std::vector<String> toPaint, int x, int y)
{
	for (int i = x, count = 0; i < x + toPaint.size(); i++, count++)
	{
		int removeWhiteSpaces = 0;
		while (toPaint[count].at(removeWhiteSpaces) == ' ')
			removeWhiteSpaces++;
		world.charWorld[i].replace(y + removeWhiteSpaces, toPaint[count].size() - removeWhiteSpaces, toPaint[count].substr(removeWhiteSpaces));
	}
}

void World::paintAt(World& world, std::vector<std::vector<WORD>> colors, int x, int y)
{
	for (int i = x, count = 0; i < x + colors.size(); i++, count++)
		for (int j = y; j < y + colors.size(); j++)
			world._colors[i][j] = colors[i - x][j - y];
		//int removeWhiteSpaces = 0;
		//while (toPaint[count].at(removeWhiteSpaces) == ' ')
		//	removeWhiteSpaces++;
		//world.charWorld[i].replace(y + removeWhiteSpaces, toPaint[count].size() - removeWhiteSpaces, toPaint[count].substr(removeWhiteSpaces));
}


void World::update()
{
	for (std::vector<IA::IAComponent*>::iterator iter = _ias.begin(); iter != _ias.end(); iter++)
	{
		IA::IAComponent* p = *iter;
		p->update();
	}
	//_ias[0]->update();

	for (auto iter = _notifyObjects.cbegin(); iter != _notifyObjects.cend();)
	{
		GameObjects::GameObject* gO = iter->first;
		Notify::GameObjectDied* gODied = iter->second;

		gO->update();

		if (!gO->isAlive())
		{
			_notifyObjects.erase(iter++);
			if (gODied != NULL)
				gODied->onGameObjectDeath(gO);
		}
		else
			++iter;
	}

	_collisionDetector->update();

	Tiles::Tile*** tiles = _tileMap->getTiles();

	for (int i = 0; i < _tileMap->height(); i++)
		for (int j = 0; j < _tileMap->width(); j++)
		{
			if (tiles[i][j]->isDestroyed())
			{
				delete tiles[i][j];
				tiles[i][j] = Tiles::Tile::createBlownUpTile(i, j);
			}
		}

	if (!_gameObjective->isAlive())
	{
		_playerWon = false;
		_gameIsFinished = true;
	}

	if (!_playerTank->isAlive())
	{
		_playerWon = false;
		_gameIsFinished = true;
	}

	if (getRemainingTanks() == 0)
	{
		_playerWon = true;
		_gameIsFinished = true;
	}
}

bool World::isValidCoordinate(int x, int y)
{
	return x >= 0 && x < getWidth() && y >= 0 && y < getHeight();
}

Tiles::Tile* World::getTileFromCoordinate(int x, int y)
{
	return _tileMap->getTiles()[(x / TILE_WIDTH)][(y / TILE_HEIGHT)];
}

int World::getElapsedSeconds()
{
	sClock_t::time_point end = sClock_t::now();

	typedef std::chrono::duration<int, std::milli> millisec_t;
	millisec_t elapsedMilli(std::chrono::duration_cast<millisec_t>(end - _startTime));
	return elapsedMilli.count() / 1000;
}

int World::getRemainingTanks()
{
	/* Account for the player Tank */
	int counter = -1;

	for (std::map<GameObjects::GameObject*, Notify::GameObjectDied*>::iterator iter = _notifyObjects.begin(); iter != _notifyObjects.end(); ++iter)
	{
		if (iter->first->getType() == GameObjects::TANK)
			counter++;
	}
	return counter;
}

void World::extractGameObjects(Tiles::TileMap& tileMap)
{
	std::vector<String> map = tileMap.rawMap();

	for (int i = 0; i < tileMap.height(); i++)
		for (int j = 0; j < tileMap.width(); j++)
		{
			int mapValue = map[i][j] - '0';

			int x = j * TILE_WIDTH;
			int y = i * TILE_HEIGHT;

			if (mapValue == Tiles::TileMap::GAMEOBJECT_PLAYER_TANK)
			{
				std::vector<std::vector<WORD>> playerTankColor(TANK_HEIGHT, std::vector<WORD>(TANK_WIDTH, FOREGROUND_WHITE | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY));
				_playerTank = new GameObjects::Tank(this, x, y, playerTankColor, true);
				addGameObject(_playerTank);
			}
			else if (mapValue == Tiles::TileMap::GAMEOBJECT_ENEMY_TANK)
			{
				std::vector<std::vector<WORD>> playerTankColor(TANK_HEIGHT, std::vector<WORD>(TANK_WIDTH, FOREGROUND_WHITE | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY));
				GameObjects::Tank* enemyTank = new GameObjects::Tank(this, x, y, playerTankColor);
				_ias.push_back(new IA::PrettyDumbIA(this, enemyTank));
				addGameObject(enemyTank);
			}
			else if (mapValue == Tiles::TileMap::GAMEOBJECT_OBJECTIVE)
			{
				_gameObjective = new GameObjects::Eagle(this, x, y);
				addGameObject(_gameObjective);
			}
		}
}
