#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "KeyboardManager.h"

using namespace std;

int mainAAA(void)
{
	cout << "Start" << endl;
	KeyboardManager k;
	int counter = 0;

	k.startManager();

	while (++counter < 200)
	{
		printf("Key pressed is: %d\n", k.getPressedKey());
		Sleep(100);
	}

	k.stopManager();

	printf("All Stopped");

	return 0;
}