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
	int _cost;

public:

	GridCell(int x, int y) { _x = x; _y = y; _cost = 0; _parent = nullptr; };

	int x() const { return _x; };
	int y() const { return _y; };

	void parent(GridCell* parent) { _parent = parent; };
	GridCell* parent() { return _parent; };

	int cost() const { return _cost; };
	void cost(int cost) { _cost = cost; };

	bool isEqual(GridCell* g) const;

	bool operator==(const GridCell& other) const;
	bool operator!=(const GridCell& other) const;
};