#pragma once
#ifndef RoB_GUI_H
#define RoB_GUI_H

#include "Game.h"
#include "Setting.h"
#include "MainMenuScreen.h"
#include "InGameScreen.h"
#include "EndGameScreen.h"

namespace Engine {
	class RoB_GUI :public Engine::Game
	{
	public:
		RoB_GUI(Setting* setting);
		~RoB_GUI();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif

