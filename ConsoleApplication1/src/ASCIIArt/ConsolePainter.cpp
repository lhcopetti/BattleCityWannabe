#include "ASCIIArt/ConsolePainter.h"
#include "Console/Console.h"


ConsolePainter::ConsolePainter(int height, int width)
{
	_height = height;
	_width = width;



	for (size_t i = 0; i < height; i++)
	{
		String str(width - 1, '_');
		_lastCharWorld.push_back(str);
	}

	for (int i = 0; i < height; i++)
	{
		_lastColors.push_back(std::vector<WORD>(width, COLOR_BACKGROUND | FOREGROUND_BLUE));
	}
}

void ConsolePainter::flip()
{

}

void ConsolePainter::paint(const std::vector<String>& charWorld, const std::vector<std::vector<WORD>>& colors)
{
	for (int i = 0; i < charWorld.size(); i++)
		checkAndPaintLine(i, charWorld[i], colors[i], _lastCharWorld[i], _lastColors[i]);


	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
		{
			_lastCharWorld[i][j] = charWorld[i][j];
			_lastColors[i][j] = colors[i][j];
		}

}

void ConsolePainter::checkAndPaintLine(int line, const String& worldLine, const std::vector<WORD>& colors, const String& lastWorldLine, const std::vector<WORD>& lastColors)
{
	for (int i = 0; i < colors.size(); i++)
	{
		if (colors[i] != lastColors[i] || worldLine[i] != lastWorldLine[i])
		{
			WORD newColor = colors[i];

			int j = i;
			while (j < colors.size() && colors[j] == newColor)
				j++;
			int colorIsEqualCounter = j - i;

			mostrar(i, line, newColor, (char*)worldLine.substr(i, colorIsEqualCounter).c_str());
		}
	}
}
