#pragma once
#include "BattleCityClone.h"
#include <vector>
#include <Windows.h>


class ConsolePainter
{
private:
	int _height;
	int _width;
	std::vector<String> _lastCharWorld;
	std::vector<std::vector<WORD>> _lastColors;

public:
	ConsolePainter(int height, int width);
	void flip();
	void paint(const std::vector<String>& charWorld, const std::vector<std::vector<WORD>>& colors);
	void checkAndPaintLine(int line, const String& worldLine, const std::vector<WORD>& colors, const String& lastWorldLine, const std::vector<WORD>& lastColors);
};