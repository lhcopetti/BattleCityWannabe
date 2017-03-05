#pragma once

#include <thread>
#include <map>
#include <Windows.h>

class KeyboardManager
{
public:

	enum class Keys
	{
		KEY_NONE,
		KEY_LEFT_ARROW,
		KEY_RIGHT_ARROW,
		KEY_UP_ARROW,
		KEY_DOWN_ARROW,
		KEY_SPACE,
		KEY_ESC
	};

	KeyboardManager();

	void startManager();
	void stopManager();

	Keys getPressedKey() const;


	static Keys currentKey;
	static std::map<KeyboardManager::Keys, WORD> keyMapping;
private:

	static bool _stopThread;
	std::thread* _keyListener;

	static void listener();
};
