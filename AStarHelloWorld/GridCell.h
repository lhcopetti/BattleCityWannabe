#pragma once


class GridCell
{
private:
	int _x;
	int _y;

	GridCell* _parent;

	//int _F; /* Total Cost */
	//int _H; /* Heuristic */
	//int _G; /* Movement Cost */
	int _heuristic;
	int _movementCost;

public:

	GridCell(int x, int y) { _x = x; _y = y; _parent = nullptr; _heuristic = 0; _movementCost = 0; };
	GridCell(const GridCell& grid);

	int x() const { return _x; };
	int y() const { return _y; };

	void parent(GridCell* parent) { _parent = parent; };
	GridCell* parent() { return _parent; };

	int cost() const { return _heuristic + _movementCost; };
	//void cost(int cost) { _cost = cost; };
	void heuristic(int h) { _heuristic = h; };
	void movementCost(int g) { _movementCost = g; };

	int movementCost() { return _movementCost; };
	int heuristic() { return _heuristic; };

	bool isEqual(GridCell* g) const;

	bool operator==(const GridCell& other) const;
	bool operator!=(const GridCell& other) const;
};