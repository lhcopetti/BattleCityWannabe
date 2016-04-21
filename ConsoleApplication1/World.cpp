#include "World.h"
#include <vector>
#include "Console\Console.h"
#include "Tiles\TileMap.h"
#include "Tiles\Tile.h"

#include <cassert>



World::World(Tiles::TileMap* tileMap)
{
	_tileMap = tileMap;
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

void World::addGameObject(Game::GameObject* go)
{
	objects.push_back(go);
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

	for each (Game::GameObject* gO in objects)
	{
		gO->paint(this);
	}

	for (int i = 0; i < getHeight(); i++)
		mostrar(0, i, BACKGROUND_WHITE | FOREGROUND_BLUE, (char*)charWorld[i].c_str());

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

}
