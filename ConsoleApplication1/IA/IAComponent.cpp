#include "IA\IAComponent.h"
#include "Commands\UnitCommand.h"

void IA::IAComponent::update()
{
	static int i = 0;

	if (i % 5 == 0)
	{
		UnitCommand::ShootCommand shootComm(_tank);
		shootComm.execute();
	}
	else
	{
		UnitCommand::GoRightCommand goRight(_tank);
		goRight.execute();
	}
	i++;
}
