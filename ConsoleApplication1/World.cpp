#include "World.h"
#include "Console\Console.h"
#include "Tiles\TileMap.h"
#include "Tiles\Tile.h"
#include "GameObjects\Eagle.h"
#include "IA\PrettyDumbIA.h"
#include "IA\IAComponent.h"

#include <sstream>
#include <cassert>

using Time = std::chrono::high_resolution_clock;

World::World(Tiles::TileMap* tileMap)
{
	_tileMap = tileMap;
	_gameIsFinished = false;

	extractGameObjects(*_tileMap);

	_startTime = std::chrono::steady_clock::now();

	clear();
}

World::~World()
{
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

	for (int i = 0; i < getHeight(); i++)
		mostrar(0, i, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)charWorld[i].c_str());

	updateFooter();

	for (int i = 0; i < _footer.size(); i++)
		mostrar(0, getHeight() + i,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)_footer[i].c_str());
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
	Time::time_point end = Time::now();

	std::chrono::duration<float> fSec = end - _startTime;

	return fSec.count();
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
				_playerTank = new GameObjects::Tank(this, x, y);
				addGameObject(_playerTank);
			}
			else if (mapValue == Tiles::TileMap::GAMEOBJECT_ENEMY_TANK)
			{
				GameObjects::Tank* enemyTank = new GameObjects::Tank(this, x, y);
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