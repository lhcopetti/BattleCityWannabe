#include "IA\PrettyDumbIA.h"

using namespace GameObjects;

IA::PrettyDumbIA::PrettyDumbIA(Tank* tank) : IAComponent(tank)
{
	_previousState = MOVE;
	_currentState = MOVE;
	cDirection = RIGHT;

}

void IA::PrettyDumbIA::update()
{

	//switch (_currentState)
	//{
	//case MOVE:
	//	if
	//	break;
	//case CHANGE_DIRECTION:
	//	break;
	//case SHOOT:
	//	break;
	//}
}