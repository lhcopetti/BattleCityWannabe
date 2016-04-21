#pragma once

#include <vector>
#include <string>

#include "BattleCityClone.h"
#include "GameObject.h"
#include "Tiles\TileMap.h"



class World
{
private:
	std::vector<String> charWorld;
	Tiles::TileMap* _tileMap;

	std::vector<Game::GameObject*> objects;
	void clear();

public:

	World(Tiles::TileMap* tileMap);
	~World();

	int getWidth() const;
	int getHeight() const;

	void update();
	void paint();

	void addGameObject(Game::GameObject* go);
	void addKeyListener(Game::GameObject* go);

	static void paintAt(World& world, std::vector<String> toPaint, int x, int y);

};