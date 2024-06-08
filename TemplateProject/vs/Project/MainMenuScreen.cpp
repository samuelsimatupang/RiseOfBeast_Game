#include "MainMenuScreen.h"

Engine::MainMenuScreen::MainMenuScreen()
{

}

void Engine::MainMenuScreen::Init()
{
	// Create a Background
	Texture* background = new Texture("mainmenu_background.png");
	backgroundSprite = (new Sprite(background, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight);

	// Create a Title Game
	Texture* title = new Texture("title.png");
	titleSprite = new Sprite(title, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	titleSprite->SetScale(1.0f);
	titleSprite->SetPosition((game->GetSettings()->screenWidth / 2) - (titleSprite->GetScaleWidth() / 2), game->GetSettings()->screenHeight - 450.0f);

	// Create a Button
	Texture* texture = new Texture("buttons.png");

	// Create Sprites
	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 5, 5)->AddAnimation("hover", 3, 4)
		->AddAnimation("press", 3, 4)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400);

	Sprite* settingSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 8, 8)->AddAnimation("hover", 6, 7)
		->AddAnimation("press", 6, 7)->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		300);
	buttons.push_back(playButton);

	Button* settingButton = new Button(settingSprite, "setting");
	settingButton->SetPosition((game->GetSettings()->screenWidth / 2) - (settingSprite->GetScaleWidth() / 2),
		225);
	buttons.push_back(settingButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		150);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);


	// Add input mappings
	game->GetInputManager()->AddInputMapping("down", SDLK_DOWN)
		->AddInputMapping("up", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}


void Engine::MainMenuScreen::Update()
{
	// Set background
	//game->SetBackgroundColor(52, 155, 235);

	if (game->GetInputManager()->IsKeyReleased("down")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("up")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::MainMenuScreen::Draw()
{
	// Render all GUI
	backgroundSprite->Draw();
	titleSprite->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	//text->Draw();
}
