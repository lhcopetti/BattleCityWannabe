#pragma once

#include <vector>
#include <string>

#include "BattleCityClone.h"
#include "GameObjects\GameObject.h"
#include "Tiles\TileMap.h"



class World
{
private:
	std::vector<String> charWorld;
	Tiles::TileMap* _tileMap;

	std::vector<GameObjects::GameObject*> objects;
	void clear();

public:

	World(Tiles::TileMap* tileMap);
	~World();

	int getWidth() const;
	int getHeight() const;

	void update();
	void paint();

	void addGameObject(GameObjects::GameObject* go);
	void addKeyListener(GameObjects::GameObject* go);

	static void paintAt(World& world, std::vector<String> toPaint, int x, int y);

};