
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
	//while (!_openList.empty())
	//{
	//	GridCell* g = _openList.top();
	//	delete g;
	//	_openList.pop();
	//}
	for (auto i = _openList.begin(); i != _openList.end(); ++i) {
		delete *i;
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

bool lowestCost(const GridCell* l, const GridCell* r)
{
	return l->cost() < r->cost();
}

class FindInSet
{
	int _x;
	int _y;

public:
	FindInSet(int x, int y) { _x = x; _y = y; };

	bool operator()(const GridCell* other)
	{
		return other->x() == _x && other->y() == _y;
	}
};

void AStar::doAStar(int startX, int startY, int endX, int endY)
{
	if (startX == endX && endY == startY)
	{
		_solved = true;
		return;
	}

	_start = new GridCell(startX, startY);
	_end = new GridCell(endX, endY);

	_openList.insert(_start);
	_onOpenList[startX][startY] = true;

	while (!_openList.empty())
	{
		auto lowCost = std::min_element(_openList.begin(), _openList.end(), lowestCost);
		GridCell* cCell = (*lowCost);
		_openList.erase(lowCost);
//		_openList.pop();
		_computation++;

		if (*cCell == *_end)
		{
			delete _end;
			_end = cCell;
			_solved = true;
			return;
		}

		std::vector<GridCell*> neighbours;
		getNeighbours(_grid, neighbours, cCell, _height, _width);

		for (GridCell* neighbour : neighbours)
		{
			if (vectorContains(_closedList, neighbour))
			{
				delete neighbour;
				continue;
			}

			neighbour->parent(cCell);
			neighbour->heuristic(computeHeuristic(neighbour, _end));
			neighbour->movementCost(cCell->movementCost() + MOVEMENT_COST);

			if (!_onOpenList[neighbour->x()][neighbour->y()])
			{
				_openList.insert(neighbour);
				_onOpenList[neighbour->x()][neighbour->y()] = true;
			}
			else
			{
				FindInSet findInSet(neighbour->x(), neighbour->y());
				auto myFindingIter = std::find_if(_openList.begin(), _openList.end(), findInSet);
				GridCell* cellInOpenList = (*myFindingIter);

				if (neighbour->cost() < cellInOpenList->cost())
				{
					_openList.erase(myFindingIter);
					_openList.insert(neighbour);

					delete cellInOpenList;
				}
				else
					delete neighbour;
				//FindInSet findInSet(neighbour->x(), neighbour->y());
				//auto myFindingIter = std::find_if(_openList.begin(), _openList.end(), findInSet);
				//if ((*myFindingIter)->cost() < neighbour->cost())
				//{
				//	cCell->movementCost((*myFindingIter)->movementCost());
				//	cCell->heuristic((*myFindingIter)->heuristic());
				//	cCell->parent((*myFindingIter)->parent());
				//}

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
