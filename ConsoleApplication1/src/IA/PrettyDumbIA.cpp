#include "IA\PrettyDumbIA.h"
#include "IA\IAAdapter.h"
#include "GameObjects\Tank.h"

#include "Commands\UnitCommand.h"
#include "World.h"
#include "GridCell.h"

using namespace GameObjects;

IA::PrettyDumbIA::PrettyDumbIA(World* world, Tank* tank) : IAComponent(world, tank)
{
	_previousState = MOVE;
	_currentState = MOVE;
	cDirection = RIGHT;
	_shoot = 0;
	_currentTarget = nullptr;
}

void IA::PrettyDumbIA::update()
{
	++ii;

	if (ii % 25 == 0)
		ii = 0;
	if (ii > 15)
		return;
	if (ii % 15 == 0)
	{
		UnitCommand::ShootCommand s(_tank);
		s.execute();
		return;
	}

	IA::IAAdapter adapter(_world);

	if (!_currentTarget)
	{
		_currentTarget = new GridCell(48, 95);
		getRandomTarget(*_currentTarget);
	}

	if (_tank->getX() == _currentTarget->x() && _tank->getY() == _currentTarget->y())
		getRandomTarget(*_currentTarget);

	GridCell* g1 = adapter.computeStep(_tank->getY(), _tank->getX(), _currentTarget->y(), _currentTarget->x());

	if (!g1)
	{
		getRandomTarget(*_currentTarget);
		return;
	}

	GridCell* g = new GridCell(g1->y(), g1->x());
	delete g1;

	if (g)
	{
		moveTank(*g);
		delete g;
	}
}

void IA::PrettyDumbIA::moveTank(GridCell& g)
{
	int currentX = _tank->getX();
	int currentY = _tank->getY();

	UnitCommand::UnitCommand* command;
	if (currentX - 1 == g.x() && currentY == g.y())
		command = new UnitCommand::GoLeftCommand(_tank);
	else if (currentX + 1 == g.x() && currentY == g.y())
		command = new UnitCommand::GoRightCommand(_tank);
	else if (currentX == g.x() && currentY - 1 == g.y())
		command = new UnitCommand::GoUpCommand(_tank);
	else if (currentX == g.x() && currentY + 1 == g.y())
		command = new UnitCommand::GoDownCommand(_tank);
	else
		command = new UnitCommand::ShootCommand(_tank);

	command->execute();
	delete command;
}

void IA::PrettyDumbIA::getRandomTarget(GridCell& gridCell)
{
	
	while (true)
	{
		int x = rand() % _world->getHeight();
		int y = rand() % _world->getWidth();


		if (IA::IAAdapter::isTankAllowedToWalk(*_world, x, y))
		{
			gridCell.x(x);
			gridCell.y(y);
			return;
		}

			//for (tankI = x; tankI < x + TANK_HEIGHT && tankI < _world->getHeight(); tankI++)
			//{
			//	for (tankJ = y; tankJ < y + TANK_WIDTH && tankJ < _world->getWidth(); tankJ++)
			//	{
			//		Tiles::Tile* t = _world->getTileFromCoordinate(tankI, tankJ);
			//		if (t->isWall() || !t->isWalkable())
			//			continue;
			//	}
			//}
	}
}
