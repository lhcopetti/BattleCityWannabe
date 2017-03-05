
#include "World.h"
#include "AStar.h"
#include "Tiles/Tile.h"
#include "IA/IAAdapter.h"

GridCell* IA::IAAdapter::computeStep(int startX, int startY, int endX, int endY)
{
	int** grid = translateWorld(*_world, startX, startY, endX, endY);

	AStar aStar(grid, _world->getHeight(), _world->getWidth(), startX, startY, endX, endY);


	GridCell* cCell;
	std::vector<GridCell*> vec;
	if (aStar.getSolution(vec) && vec.size() > 0)
		cCell = new GridCell(*vec[0]);
	else
		cCell = nullptr;

	for (int i = 0; i < _world->getHeight(); i++)
		delete[] grid[i];
	delete grid;

	return cCell;
}

int** IA::IAAdapter::translateWorld(World& world, int startX, int startY, int endX, int endY)
{
	int** grid;

	grid = new int*[world.getHeight()];
	for (int i = 0; i < world.getHeight(); i++)
		grid[i] = new int[world.getWidth()];

	for (int i = 0; i < world.getHeight(); i++)
		for (int j = 0; j < world.getWidth(); j++)
			grid[i][j] = isTankAllowedToWalk(world, i, j) ? EMPTY_COORD : CLOSED_COORD;

	return grid;
}

bool IA::IAAdapter::isTankAllowedToWalk(World& world, int i, int j)
{
	for (int tankI = i; tankI < i + TANK_HEIGHT && tankI < world.getHeight(); tankI++)
	{
		for (int tankJ = j; tankJ < j + TANK_WIDTH && tankJ < world.getWidth(); tankJ++)
		{
			Tiles::Tile* t = world.getTileFromCoordinate(tankI, tankJ);
			if (t->isWall() || !t->isWalkable())
				return false;
		}
	}

	return true;
}
