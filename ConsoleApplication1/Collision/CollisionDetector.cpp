#include "CollisionDetector.h"

#include "GameObjects\Missile.h"
#include "GameObjects\GameObject.h"
#include "World.h"

using namespace Collision;

CollisionDetector::CollisionDetector(World* world) 
{
	_world = world;
	_world->setCollisionDetector(this);
}

void CollisionDetector::update()
{

	for (auto iter = _world->getObjects().cbegin(); iter != _world->getObjects().cend(); iter++)
	{
		GameObjects::GameObject* gO = iter->first;
		if (gO->getType() == GameObjects::MISSILE)
		{
			GameObjects::Missile* missile = static_cast<GameObjects::Missile*>(gO);
			missile->onTile(_world->getTileFromCoordinate(missile->getY(), missile->getX()));
		}
	}

}