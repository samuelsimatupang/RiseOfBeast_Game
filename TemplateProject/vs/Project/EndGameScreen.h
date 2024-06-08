#ifndef ENDGAMESCREEN_H
#define ENDGAMESCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class EndGameScreen :
		public Engine::Screen
	{
	public:
		EndGameScreen();
		void Init();
		void Update();
		void Draw();
	private:
		vector<Button*> buttons;
		Text* text = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* gameOverSprite = NULL;
		int currentButtonIndex = 0;
	};
}

#endif