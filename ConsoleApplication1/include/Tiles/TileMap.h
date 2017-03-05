#pragma once

#include "../BattleCityClone.h"
#include "GameObjects\GameObject.h"
#include "GameObjects\Tank.h"
#include "Tile.h"

namespace Tiles
{

	class TileMap
	{
	private:
		Tile*** _tiles;
		GameObjects::Tank* _playerTank;
		std::vector<GameObjects::GameObject> _gameObjects;
		std::vector<String> map;

		int _height;
		int _width;

		TileMap();

	public:

		enum TileObjects
		{
			TILE_GROUND = 0,
			TILE_BRICK = 1,
			TILE_INDESTRUCTIBLE = 2,
			GAMEOBJECT_OBJECTIVE = 7,
			GAMEOBJECT_PLAYER_TANK = 8,
			GAMEOBJECT_ENEMY_TANK = 9
		};

		TileMap(String fileName);
		~TileMap();

		int height();
		int width();
		const std::vector<String> rawMap() const { return map; };
		Tiles::Tile*** getTiles();

		GameObjects::Tank* getPlayerTank() const { return _playerTank; };
	};

}