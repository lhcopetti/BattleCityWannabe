#pragma once

#include "GridCell.h"

#include <vector>
#include <queue>
#include <functional>
#include <set>

#define EMPTY_COORD 0
#define CLOSED_COORD 1
#define START_COORD 2
#define END_COORD 3

#define MOVEMENT_COST 10
#define HEURISTIC_COST 20

class AStar
{
private:

	int** _grid;
	int _height;
	int _width;
	bool _solved;
	int _computation;

	bool** _onOpenList;

	GridCell* _start;
	GridCell* _end;

	struct UniqueCoord
	{
		bool operator()(const GridCell* left, const GridCell* right) const
		{
			if (left->x() < right->x()) return true;
			if (left->x() > right->x()) return false;
			// x == x

			if (left->y() < right->y()) return true;
			if (left->y() > right->y()) return false;
			// y == y

			return false;
//			return left->x() < right->x() || left->y() < right->y();
		}
	};

	//std::priority_queue<GridCell*, std::vector<GridCell*>, InversePriority> _openList;
	std::set<GridCell*, UniqueCoord> _openList;
	std::vector<GridCell*> _closedList;

	void doAStar(int startX, int startY, int endX, int endY);
public:
	AStar(int** grid, int height, int width, int startX, int startY, int endX, int endY);
	~AStar();

	static void getNeighbours(int** grid, std::vector<GridCell*>& vector, GridCell* currentCell, int height, int width);
	static bool vectorContains(std::vector<GridCell*> &list, GridCell* g);
	static int computeHeuristic(GridCell* currentNode, GridCell* end);

	bool getSolution(std::vector<GridCell*> &vector) const;

};