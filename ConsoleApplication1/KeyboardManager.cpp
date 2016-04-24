#include "KeyboardManager.h"

#include <conio.h>
#include <stdio.h>

void windowsKeyEvent(KEY_EVENT_RECORD ker);

bool KeyboardManager::_stopThread = false;
KeyboardManager::Keys KeyboardManager::currentKey = KeyboardManager::Keys::KEY_NONE;
std::map<KeyboardManager::Keys, WORD>  KeyboardManager::keyMapping;

KeyboardManager::KeyboardManager()
{
	KeyboardManager::currentKey = Keys::KEY_NONE;
	_keyListener = nullptr;
	KeyboardManager::_stopThread = false;

	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_NONE] = 0;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_UP_ARROW] = 72;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_DOWN_ARROW] = 80;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_LEFT_ARROW] = 75;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_RIGHT_ARROW] = 77;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_SPACE] = 57;
	KeyboardManager::keyMapping[KeyboardManager::Keys::KEY_ESC] = 0;
}

void KeyboardManager::startManager()
{
	_keyListener = new std::thread(listener);
}

void KeyboardManager::listener()
{
	HANDLE hStdin;
	DWORD fdwSaveOldMode;

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	// Save the current input mode, to be restored on exit. 
	//if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
	//	ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	//if (!SetConsoleMode(hStdin, fdwMode))
	//	ErrorExit("SetConsoleMode");
	SetConsoleMode(hStdin, fdwMode);

	while (!_stopThread)
	{
		// Wait for the events. 

		ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead); // number of records read 

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				windowsKeyEvent(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input [Ignore]
			default:
				break;
			}
		}
	}
}

void KeyboardManager::stopManager()
{
	KeyboardManager::_stopThread = true;
	_keyListener->join();
}

KeyboardManager::Keys KeyboardManager::getPressedKey() const
{
	return KeyboardManager::currentKey;
}

void windowsKeyEvent(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
	{
		for (auto iter = KeyboardManager::keyMapping.begin(); iter != KeyboardManager::keyMapping.end(); ++iter)
		{
			KeyboardManager::Keys keyMap = iter->first;
			WORD keyWord = iter->second;

			if (ker.wVirtualScanCode == keyWord)
				KeyboardManager::currentKey = keyMap;
		}
	}
	else if(ker.wVirtualScanCode == KeyboardManager::keyMapping[KeyboardManager::currentKey])
	{
		KeyboardManager::currentKey = KeyboardManager::Keys::KEY_NONE;
	}
		//switch (ker.wVirtualScanCode)
		//{
		//case 72:
		//	KeyboardManager::currentKey = KeyboardManager::Keys::KEY_UP_ARROW;
		//	break;
		//case 75:
		//	KeyboardManager::currentKey = KeyboardManager::Keys::KEY_LEFT_ARROW;
		//	break;
		//case 77:
		//	KeyboardManager::currentKey = KeyboardManager::Keys::KEY_RIGHT_ARROW;
		//	break;
		//case 80:
		//	KeyboardManager::currentKey = KeyboardManager::Keys::KEY_DOWN_ARROW;
		//	break;
		//case 32:
		//	KeyboardManager::currentKey = KeyboardManager::Keys::KEY_SPACE;
		//	break;
		//}
}