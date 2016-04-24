
#include "GridCell.h"

bool GridCell::isEqual(GridCell* g) const
{
	return _x == g->x() && _y == g->y();
}

bool GridCell::operator==(const GridCell& other) const
{
	return _x == other.x() && _y == other.y();
}

bool GridCell::operator!=(const GridCell& other) const
{
	return !(*this == other);
}