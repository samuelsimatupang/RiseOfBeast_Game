#include "MainMenuScreen.h"
#include "EndGameScreen.h"

Engine::EndGameScreen::EndGameScreen() 
{

}

void Engine::EndGameScreen::Init()
{
	// Create a Background
	Texture* background = new Texture("mainmenu_background.png");
	backgroundSprite = (new Sprite(background, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight);

	// Create a Game Over Sign
	Texture* title = new Texture("game_over.png");
	gameOverSprite = new Sprite(title, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameOverSprite->SetScale(1.0f);
	gameOverSprite->SetPosition((game->GetSettings()->screenWidth / 2) - (gameOverSprite->GetScaleWidth() / 2), game->GetSettings()->screenHeight - 450.0f);

	// Create a Button
	Texture* texture = new Texture("buttons.png");

	// Create Sprites
	Sprite* retrySprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 11, 11)->AddAnimation("hover", 9, 10)
		->AddAnimation("press", 9, 10)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400);

	Sprite* mainMenuSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 14, 14)->AddAnimation("hover", 12, 13)
		->AddAnimation("press", 12, 13)->SetAnimationDuration(400);

	//Create Buttons
	Button* retryButton = new Button(retrySprite, "retry");
	retryButton->SetPosition((game->GetSettings()->screenWidth / 2) - (retrySprite->GetScaleWidth() / 2),
		300);
	buttons.push_back(retryButton);

	Button* mainMenuButton = new Button(mainMenuSprite, "mainMenu");
	mainMenuButton->SetPosition((game->GetSettings()->screenWidth / 2) - (mainMenuSprite->GetScaleWidth() / 2),
		225);
	buttons.push_back(mainMenuButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		150);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	/*text = new Text("Semper Invicta.ttf", 150, game->GetDefaultTextShader());
	text->SetText("Rise of Beast");
	text->SetPosition((game->GetSettings()->screenWidth / 2) - (text->GetWidth() / 2), game->GetSettings()->screenHeight - 200.0f);
	text->SetColor(255, 255, 255);*/

	// Add input mappings
	game->GetInputManager()->AddInputMapping("down", SDLK_DOWN)
		->AddInputMapping("up", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}

void Engine::EndGameScreen::Update()
{
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
		if ("retry" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
		}
		else if ("mainMenu" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
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

void Engine::EndGameScreen::Draw()
{
	// Render all GUI
	backgroundSprite->Draw();
	gameOverSprite->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
}