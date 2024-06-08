#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <unordered_map>

using namespace std;
using namespace glm;

namespace Engine {
	class Input
	{
	public:
		bool IsKeyPressed(string name);
		bool IsKeyPressed(string name, string screenName); 
		bool IsKeyReleased(string name);
		bool IsKeyReleased(string name, string screenName);
		vec2 GetMouseCoords();
		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);
		void SetMouseCoords(float x, float y);
		void OpenGameController();
		void CloseGameController();
		Engine::Input* AddInputMapping(string mappingName, unsigned int keyId);
		Engine::Input* AddInputMapping(string mappingName, unsigned int keyId, string screenName); 
		void Reset();
	
	private:
		vec2 mouseCoords;
		SDL_GameController* controller;
		unordered_map<unsigned int, string> keyCodeNameMap;
		unordered_map<string, bool> pressedKeyMap;
		vector<string> releasedKeys;

		unordered_map<unsigned int, string> mainMenuKeyCodeNameMap;
		unordered_map<string, bool> mainMenuPressedKeyMap;
		vector<string> mainMenuReleasedKeys;

		unordered_map<unsigned int, string> inGameKeyCodeNameMap;
		unordered_map<string, bool> inGamePressedKeyMap;
		vector<string> inGameReleasedKeys;
	};
}

#endif
