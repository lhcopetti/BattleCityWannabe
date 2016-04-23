#pragma once

#include <vector>
#include <map>
#include <string>

#include "BattleCityClone.h"
#include "GameObjects\GameObject.h"
#include "Tiles\TileMap.h"
#include "Notify\GameObjectDied.h"
#include "Collision\CollisionDetector.h"


class World
{
private:
	std::vector<String> charWorld;
	Tiles::TileMap* _tileMap;

	std::map<GameObjects::GameObject*, Notify::GameObjectDied*> _notifyObjects;
	Collision::CollisionDetector* _collisionDetector;

	void clear();

public:

	World(Tiles::TileMap* tileMap);
	~World();

	int getWidth() const;
	int getHeight() const;

	std::map<GameObjects::GameObject*, Notify::GameObjectDied*> &getObjects() { return _notifyObjects; };

	void setCollisionDetector(Collision::CollisionDetector* coll) { _collisionDetector = coll; };

	void update();
	void paint();

	void addGameObject(GameObjects::GameObject* go);
	void addGameObject(GameObjects::GameObject* gO, Notify::GameObjectDied* gDied);
	void addKeyListener(GameObjects::GameObject* go);

	bool isValidCoordinate(int x, int y);
	Tiles::Tile* getTileFromCoordinate(int x, int y);

	static void paintAt(World& world, std::vector<String> toPaint, int x, int y);

};