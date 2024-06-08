#include "RoB_GUI.h"

Engine::RoB_GUI::RoB_GUI(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Rise of Beast";
}

Engine::RoB_GUI::~RoB_GUI()
{
}

void Engine::RoB_GUI::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new InGameScreen())
		->AddScreen("mainmenu", new MainMenuScreen())->AddScreen("endgame", new EndGameScreen())
		->SetCurrentScreen("mainmenu");

}

void Engine::RoB_GUI::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::RoB_GUI::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}
