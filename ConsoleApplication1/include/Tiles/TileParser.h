#pragma once

#include "Tile.h"
#include "../BattleCityClone.h"
#include "TileMap.h"

#define MAP_HEIGHT 13
#define MAP_WIDTH 13

class TileParser
{
private:
	String fileName;

public:
	TileParser(String fileName);
	~TileParser();
};