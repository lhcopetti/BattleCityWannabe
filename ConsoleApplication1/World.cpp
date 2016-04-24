#include "World.h"
#include <vector>
#include "Console\Console.h"
#include "Tiles\TileMap.h"
#include "Tiles\Tile.h"

#include <sstream>
#include <cassert>

using Time = std::chrono::high_resolution_clock;

World::World(Tiles::TileMap* tileMap)
{
	_tileMap = tileMap;


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
		mostrar(0, i, BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)charWorld[i].c_str());

	updateFooter();

	for (int i = 0; i < _footer.size(); i++)
		mostrar(0, getHeight() + i, BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, (char*)_footer[i].c_str());
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
	//std::chrono::duration<double> d= std::chrono::duration_cast<std::chrono::duration<int>>(end - _startTime);
	//return d.count;
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