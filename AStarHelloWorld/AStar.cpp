
#include <algorithm>
#include <math.h>
#include <iostream>

#include "AStar.h"
#include "GridCell.h"


void deletePointer(GridCell* ptr)
{
	delete ptr;
}

AStar::~AStar()
{
	while (!_openList.empty())
	{
		GridCell* g = _openList.top();
		delete g;
		_openList.pop();
	}

	std::for_each(_closedList.begin(), _closedList.end(), deletePointer);

//	delete _start;
	delete _end;
}

AStar::AStar(int** grid, int height, int width, int startX, int startY, int endX, int endY)
{
	_grid = grid;
	_height = height;
	_width = width;

	_start = nullptr;
	_end = nullptr;

	_computation = 0;

	_onOpenList = new bool*[height];
	for (int i = 0; i < _height; i++)
		_onOpenList[i] = new bool[width];

	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_onOpenList[i][j] = false;

	doAStar(startX, startY, endX, endY);
}

void AStar::doAStar(int startX, int startY, int endX, int endY)
{

	if (startX == endX && endY == startY)
	{
		_solved = true;
		return;
	}

	_start = new GridCell(startX, startY);
	_end = new GridCell(endX, endY);

	_openList.push(_start);
	_onOpenList[startX][startY] = true;

	while (!_openList.empty())
	{
		GridCell* cCell = _openList.top();
		_openList.pop();
		_computation++;

		if (*cCell == *_end)
		{
			delete _end;
			_end = cCell;
			_solved = true;
		//	std::cout << "Found a solution" << std::endl;
			return;
		}

		std::vector<GridCell*> neighbours;
		getNeighbours(_grid, neighbours, cCell, _height, _width);

		for each (GridCell* neighbour in neighbours)
		{
			if (vectorContains(_closedList, neighbour))
			{
				delete neighbour;
				continue;
			}

			if (!_onOpenList[neighbour->x()][neighbour->y()])
			{
				neighbour->parent(cCell);
				neighbour->heuristic(computeHeuristic(neighbour, _end));
				neighbour->movementCost(cCell->movementCost() + MOVEMENT_COST);

				_openList.push(neighbour);
				_onOpenList[neighbour->x()][neighbour->y()] = true;
			}
		}

		_closedList.push_back(cCell);
	}

	_solved = false;
}

bool AStar::getSolution(std::vector<GridCell*> &vector) const
{
	if (!_solved)
		return false;

	if (_end == nullptr)
		/* Start == End */
		return true;

	std::vector<GridCell*>::iterator it;

	GridCell* cCell = _end;
	vector.clear();
	do
	{
		it = vector.begin();
		vector.insert(it, cCell);
		cCell = cCell->parent();
	} while (cCell != _start);

	return true;
}

void AStar::getNeighbours(int** grid, std::vector<GridCell*>& vector, GridCell* currentCell, int height, int width)
{
	int operators[4][2] = { {-1,0},{0,1},{1,0},{0, -1} };

	for (int i = 0; i < 4; i++)
	{
		int x = currentCell->x() + operators[i][0];
		int y = currentCell->y() + operators[i][1];

		if (x < 0 || x >= height || y < 0 || y >= width)
			continue;
		if (grid[x][y] == CLOSED_COORD)
			continue;

		GridCell* newCell = new GridCell(x, y);
		vector.push_back(newCell);
	}
}

template <typename T>
struct pointer_values_equal
{
	const T* to_find;

	bool operator()(const T* other) const
	{
		return *to_find == *other;
	}
};

bool AStar::vectorContains(std::vector<GridCell*> &list, GridCell* g)
{
	pointer_values_equal<GridCell> pred = { g };

	if (std::find_if(list.begin(), list.end(), pred) == list.end())
		return false;
	return true;
}

int AStar::computeHeuristic(GridCell* currentNode, GridCell* end)
{
	return  HEURISTIC_COST * (int)(abs(currentNode->x() - end->x()) + abs(currentNode->y() - end->y()) + 0.5);
}