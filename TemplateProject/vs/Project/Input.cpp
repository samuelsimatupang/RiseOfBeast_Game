#include "Input.h"

using namespace Engine;

bool Input::IsKeyPressed(string name)
{
	auto it = pressedKeyMap.find(name);
	if (it != pressedKeyMap.end()) {
		// Found the key
		return it->second;
	}

	// Didn't find the key
	return false;
}

bool Input::IsKeyPressed(string name, string screenName)
{
	if (screenName == "mainmenu") {
		auto it = mainMenuPressedKeyMap.find(name);
		if (it != mainMenuPressedKeyMap.end()) {
			// Found the key
			return it->second;
		}
	}
	if (screenName == "ingame") {
		auto it = inGamePressedKeyMap.find(name);
		if (it != inGamePressedKeyMap.end()) {
			// Found the key
			return it->second;
		}
	}

	// Didn't find the key
	return false;
}

bool Input::IsKeyReleased(string name)
{
	for (auto& val : releasedKeys) // access by reference to avoid copying
	{
		if (val == name)
		{
			return true;
		}
	}
	// Didn't find
	return false;
}

bool Input::IsKeyReleased(string name, string screenName)
{
	if (screenName == "mainmenu")
	{
		for (auto& val : mainMenuReleasedKeys) // access by reference to avoid copying
		{
			if (val == name)
			{
				return true;
			}
		}
	}
	if (screenName == "ingame")
	{
		for (auto& val : inGameReleasedKeys) // access by reference to avoid copying
		{
			if (val == name)
			{
				return true;
			}
		}
	}
	// Didn't find
	return false;
}

vec2 Input::GetMouseCoords()
{
	return this->mouseCoords;
}

Engine::Input* Input::AddInputMapping(string mapName, unsigned int keyId)
{

	if (keyCodeNameMap.count(keyId) > 0) {
		keyCodeNameMap.erase(keyId);
	}

	keyCodeNameMap.insert(pair<unsigned int, string>(keyId, mapName));
	return this;
}

Engine::Input* Input::AddInputMapping(string mapName, unsigned int keyId, string screenName)
{
	// Map khusus untuk setiap layar
	if (screenName == "mainmenu") {
		if (mainMenuKeyCodeNameMap.count(keyId) > 0) {
			mainMenuKeyCodeNameMap.erase(keyId);
		}
		mainMenuKeyCodeNameMap.insert(pair<unsigned int, string>(keyId, mapName));
	}
	if (screenName == "ingame") {
		if (inGameKeyCodeNameMap.count(keyId) > 0) {
			inGameKeyCodeNameMap.erase(keyId);
		}
		inGameKeyCodeNameMap.insert(pair<unsigned int, string>(keyId, mapName));
	}

	return this;
}

void Engine::Input::Reset()
{
	releasedKeys.clear();
}

void Input::PressKey(unsigned int keyID)
{
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = keyCodeNameMap.find(keyID);
	if (it != keyCodeNameMap.end()) {
		string mapName = it->second;
		pressedKeyMap[mapName] = true;
		return;
	}
}

void Input::ReleaseKey(unsigned int keyID)
{
	auto it = keyCodeNameMap.find(keyID);
	if (it != keyCodeNameMap.end()) {
		string mapName = it->second;
		pressedKeyMap[mapName] = false;
		releasedKeys.push_back(mapName);
	}
}

void Input::SetMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}

void Input::OpenGameController()
{
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(0))
		{
			controller = SDL_GameControllerOpen(0);
			if (controller != nullptr)
				cout << "Game Controller is Detected" << endl;
		}
	}
}

void Input::CloseGameController()
{
	if (controller != nullptr) {
		SDL_GameControllerClose(0);
		cout << "Game Controller is Removed" << endl;
	}
}
