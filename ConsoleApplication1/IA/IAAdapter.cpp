
#include "IAAdapter.h"
#include "World.h"
#include "AStar.h"
#include "Tiles\Tile.h"

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
		{
			//if (i == startX && j == startY)
			//	grid[i][j] = START_COORD;
			//else if (i == endX && j == endY)
			//	grid[i][j] = END_COORD;
			//else
			//{
				Tiles::Tile* t = world.getTileFromCoordinate(i, j);
				if (t->isWalkable())
					grid[i][j] = EMPTY_COORD;
				else
					grid[i][j] = CLOSED_COORD;
//			}
		}

	return grid;
}