#pragma once

#include <vector>
#include <map>
#include <string>
#include <chrono>

#include "BattleCityClone.h"
#include "GameObjects\GameObject.h"
#include "Tiles\TileMap.h"
#include "Notify\GameObjectDied.h"
#include "Collision\CollisionDetector.h"
#include "IA\IAComponent.h"
#include "ASCIIArt\ConsolePainter.h"

class World
{
private:
	std::vector<String> charWorld;
	std::vector<std::vector<WORD>> _colors;
	Tiles::TileMap* _tileMap;
	ConsolePainter* _painter;


	std::map<GameObjects::GameObject*, Notify::GameObjectDied*> _notifyObjects;
	Collision::CollisionDetector* _collisionDetector;

	std::vector<IA::IAComponent*> _ias;

	std::vector<String> _footer;

	bool _playerWon;
	bool _gameIsFinished;

	GameObjects::Tank* _playerTank;
	GameObjects::Eagle* _gameObjective;

	void clear();

	int getElapsedSeconds();
	int getRemainingTanks();
	void updateFooter();

	void extractGameObjects(Tiles::TileMap& tileMap);

	typedef std::chrono::steady_clock sClock_t;
	sClock_t::time_point _startTime;

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

	GameObjects::Tank* getPlayerTank() const { return _playerTank; };
	GameObjects::Eagle* getGameObjective() const { return _gameObjective; };

	bool getGameIsFinished() const { return _gameIsFinished; };
	bool getPlayerWon() const { return _playerWon; };

	bool isValidCoordinate(int x, int y);
	Tiles::Tile* getTileFromCoordinate(int x, int y);

	static void paintAt(World& world, std::vector<String> toPaint, int x, int y);
	static void paintAt(World& world, std::vector<std::vector<WORD>> colors, int x, int y);

};
