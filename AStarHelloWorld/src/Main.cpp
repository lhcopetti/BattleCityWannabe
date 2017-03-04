#include <iostream>
#include <string>

#include "GridCell.h"
#include "AStar.h"

#define START 1
#define OBJECTIVE 8
#define WALL 6

using namespace std;

void printCells(std::vector<GridCell*> cells)
{
	for (int i = 0; i < cells.size(); i++)
		cout << "Cell#" << i << " : [" << cells[i]->x() << "][" << cells[i]->y() << "] | " << endl;
	cout << endl;
}

void printMatrix(int **matrix, int width, int height);

int mainNot()
{
	int height = 6;
	int width = 6;
	int myMatrix[6][6] = {
		{0, 0, 0, 0, 0, 0 },
		{0, 2, 0, 1, 0, 0 },
		{0, 0, 1, 1, 0, 1 },
		{1, 1, 1, 0, 0, 1 },
		{1, 1, 0, 0, 1, 0 },
		{3, 0, 0, 0, 0, 0 }
	};

	//int height = 4;
	//int width = 4;
	//int myMatrix[4][4]
	//{
	//		{ 2, 0, 0, 0 },
	//		{ 0, 1, 0, 0 },
	//		{ 1, 3, 0, 1 },
	//		{ 1, 1, 0, 0 } 
	//};

	//GridCell* t = new GridCell(3, 3);
	//GridCell* ttt = new GridCell(3, 3);
	////GridCell* t2t = new GridCell(3, 3);
	//std::vector<GridCell*> closedList;
	//closedList.push_back(t);
	//if (AStar::vectorContains(closedList, ttt))
	//	cout << "Contains" << endl;
	//else
	//	cout << "Doesnt " << endl;

	//return 0;

	int **matrix;
	matrix = new int*[height];
	for (int i = 0; i < height; i++)
		matrix[i] = new int[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			matrix[i][j] = myMatrix[i][j];

	std::cout << "Test" << endl;

	printMatrix(matrix, height, width);

	for (int i = 0; i < 10000; i++)
	{
		//AStar aStart(matrix, height, width);

	//	std::vector<GridCell*> vector;
/*		if (aStart.getSolution(vector))
			printCells(vector);*/
	}
	for (int i = 0; i < height; i++)
		delete matrix[i];
	delete[] matrix;

	string myString;
	cin >> myString;

	return 0;
}

void printMatrix(int **matrix, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}