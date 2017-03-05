#include "Collision/CollisionDetector.h"

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

	for (auto iter = _world->getObjects().cbegin(); iter != _world->getObjects().cend(); ++iter)
	{
		for (auto iterInt = _world->getObjects().cbegin(); iterInt != _world->getObjects().cend(); ++iterInt)
		{
			if (iter == iterInt)
				continue;

			checkCollision(iter->first, iterInt->first);
		}
		GameObjects::GameObject* gO = iter->first;
		if (gO->getType() == GameObjects::MISSILE)
		{
			GameObjects::Missile* missile = static_cast<GameObjects::Missile*>(gO);
			missile->onTile(_world->getTileFromCoordinate(missile->getY(), missile->getX()));
		}
	}

}

void CollisionDetector::checkCollision(GameObjects::GameObject* goA, GameObjects::GameObject* goB)
{
	int goA_X1 = goA->getX(), goA_X2 = goA->getX() + goA->width();
	int goA_Y1 = goA->getY(), goA_Y2 = goA->getY() + goA->height();

	int goB_X1 = goB->getX(), goB_X2 = goB->getX() + goB->width();
	int goB_Y1 = goB->getY(), goB_Y2 = goB->getY() + goB->height();

	if (goA_X1 < goB_X2 && goA_X2 > goB_X1 && goA_Y1 < goB_Y2 && goA_Y2 > goB_Y1)
	{
		goA->collide(goB);
		goB->collide((Collidable*)goA);
	}
}
