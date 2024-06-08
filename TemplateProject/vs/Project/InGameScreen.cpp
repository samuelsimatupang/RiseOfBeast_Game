#include "InGameScreen.h"

Engine::InGameScreen::InGameScreen()
{
	spawnTimer = 0.0f;
	hero = NULL;
	enemyHits = 0;
	totalScore = 0;
	totalHealth = 5;
}

void Engine::InGameScreen::Init()
{
	// Create a Background
	Texture* background = new Texture("ingame_background.png");
	backgroundSprite = (new Sprite(background, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight);

	// Add a player 
	texture = new Texture("s8dchars.png");
	hero = new Hero(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	hero->SetPosition(game->GetSettings()->screenWidth / 2.0f - hero->GetSprite()->GetScaleWidth(), game->GetSettings()->screenHeight / 2.0f);
	// Collision Detection for Player
	/*hero->GetSprite()->SetBoundingBoxSize(hero->GetSprite()->GetScaleWidth() - (16 * hero->GetSprite()->GetScale()),
		hero->GetSprite()->GetScaleHeight() - (4 * hero->GetSprite()->GetScale()));*/

	// Add bullets
	bulletTexture = new Texture("bullet.png");
	int bulletNum = 50;
	for (int i = 0; i < bulletNum; i++) {
		Sprite* bs = (new Sprite(bulletTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetNumXFrames(1)->SetNumYFrames(1)->SetScale(1);
		readyBullets.push_back(new Bullet(bs));
	}
	
	healthBarText = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	healthBarText->SetText("Total health : " + to_string(totalHealth));
	healthBarText->SetPosition(10.0f, game->GetSettings()->screenHeight - 30.0f);
	healthBarText->SetColor(255, 255, 255);

	scoreText = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	scoreText->SetText("Score : " + to_string(totalScore));
	scoreText->SetPosition(10.0f, game->GetSettings()->screenHeight - 60.0f);
	scoreText->SetColor(255, 255, 255);

	// Add input mappings
	hero->Init(game->GetInputManager());
	game->GetInputManager()->AddInputMapping("attack", SDLK_x);
	game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);

}

void Engine::InGameScreen::Update()
{
	// Back to main menu
	if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
		enemyHits = 0;
		enemies.clear();
		hero->SetPosition(game->GetSettings()->screenWidth / 2.0f - hero->GetSprite()->GetScaleWidth(), game->GetSettings()->screenHeight / 2.0f);
		totalScore = 0;
		totalHealth = 0;
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
	}

	if (game->GetInputManager()->IsKeyPressed("attack")) {
		SpawnBullets();
	}

	//// Spawn Enemies
	Enemy* enemy;
	spawnTimer += game->GetGameTime();
	if (spawnTimer >= 1000) {
		// create a new enemy
		enemy = new Enemy(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		// Set random enemy's position
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> disX(0, game->GetSettings()->screenWidth);
		float enemyX = (float)disX(gen);
		uniform_int_distribution<> disY(0, game->GetSettings()->screenHeight);
		float enemyY = (float)disY(gen);
		uniform_int_distribution<> disBorder(0, 3);
		int border = disBorder(gen);
		// 0 = spawn from bottom, 1 = left, 2 = top, 3 = right
		if (0 == border) {
			enemyY = -enemy->GetSprite()->GetScaleHeight();
		}
		else if (1 == border) {
			enemyX = -enemy->GetSprite()->GetScaleWidth();
		}
		else if (2 == border) {
			enemyY = (float)game->GetSettings()->screenHeight;
		}
		else {
			enemyX = (float)game->GetSettings()->screenWidth;
		}
		enemy->SetPosition(enemyX, enemyY);
		enemy->SetMaxSpeed(0.05f);
		enemy->SetTarget(hero);
		enemy->GetSprite()->SetBoundingBoxSize(enemy->GetSprite()->GetScaleWidth() - (16 * enemy->GetSprite()->GetScale()),
			enemy->GetSprite()->GetScaleHeight() - (4 * enemy->GetSprite()->GetScale()));
		enemies.push_back(enemy);
		spawnTimer = 0;
	}

	//bullet setting
	timeInterval += game->GetGameTime();
	for (Bullet* b : inUseBullets) {
		b->sprite->SetBoundingBoxSize(b->sprite->GetScaleWidth() - (16 * b->sprite->GetScale()),
			b->sprite->GetScaleHeight());
		// If bullet off screen then remove a bullet from in-use container, and insert into ready-to-use container
		if (b->GetPosition().x < -b->sprite->GetScaleWidth() || b->GetPosition().x > game->GetSettings()->screenWidth || b->GetPosition().y < -b->sprite->GetScaleHeight() || b->GetPosition().y > game->GetSettings()->screenHeight) {
			readyBullets.push_back(b);
			inUseBullets.erase(remove(inUseBullets.begin(), inUseBullets.end(), b), inUseBullets.end());
		}
		b->Update(game->GetGameTime());
	}

	for (Enemy* e : enemies) {
		// Collision setting bullet with enemy
		for (Bullet* b : inUseBullets) {
			if (b->sprite->GetBoundingBox()->CollideWith(e->GetSprite()->GetBoundingBox())) {
				readyBullets.push_back(b);
				inUseBullets.erase(remove(inUseBullets.begin(), inUseBullets.end(), b), inUseBullets.end());
				//enemies.push_back(enemy);
				enemies.erase(remove(enemies.begin(), enemies.end(), e), enemies.end());
				totalScore += 20;
				break;
			}
		}
		// Collision setting hero with enemy
		if (e->GetSprite()->GetBoundingBox()->CollideWith(hero->GetSprite()->GetBoundingBox())) {
			if (!e->hasHitHero) {
				enemyHits++;
				totalHealth--;
				e->hasHitHero = true;
				std::cout << "Hero hit by enemy! Total hits: " << enemyHits << std::endl;
			}

		}
		else {
			e->hasHitHero = false;
		}

		// Cek apakah pemain sudah dikenai enemy sebanyak 5 kali
		if (enemyHits >= 5) {
			std::cout << "Hero hit 5 times. Returning to main menu." << std::endl;
			enemyHits = 0;
			enemies.clear();
			hero->SetPosition(game->GetSettings()->screenWidth / 2.0f - hero->GetSprite()->GetScaleWidth(), game->GetSettings()->screenHeight / 2.0f);
			totalScore = 0;
			totalHealth = 5;
			ScreenManager::GetInstance(game)->SetCurrentScreen("endgame");
		}

		e->Update(game->GetGameTime());
	}
	healthBarText->SetText("Your health : " + to_string(totalHealth));
	scoreText->SetText("Score : " + to_string(totalScore));

	// Set position hero
	vec2 oldHeroPosition = hero->GetPosition();
	hero->Update(game->GetGameTime());
	if (hero->GetPosition().x < 0 || hero->GetPosition().x > game->GetSettings()->screenWidth - hero->GetSprite()->GetScaleWidth()) {
		hero->SetPosition(oldHeroPosition.x, hero->GetPosition().y);
	}
	if (hero->GetPosition().y < 0 || hero->GetPosition().y > game->GetSettings()->screenHeight - hero->GetSprite()->GetScaleHeight()) {
		hero->SetPosition(hero->GetPosition().x, oldHeroPosition.y);
	}
}

void Engine::InGameScreen::Draw()
{
	// Render all objects
	backgroundSprite->Draw();
	healthBarText->Draw();
	scoreText->Draw();
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}
	for (Bullet* b : inUseBullets) {
		b->Draw();
	}
	hero->Draw();

}

void Engine::InGameScreen::SpawnBullets()
{
	if (timeInterval >= 150) {
		if (readyBullets.empty()) {
			return;
		}
		Bullet* b = readyBullets.back();
		readyBullets.pop_back();
		b->SetPosition(hero->GetPosition().x, hero->GetPosition().y + hero->GetSprite()->GetScaleHeight() * 0.2f);

		string direction = hero->GetDirection();
		b->SetDirection(direction);

		if (direction == "right" || direction == "left") {
			b->xVelocity = 0.6f;
		}
		if (direction == "up" || direction == "down") {
			b->yVelocity = 0.6f;
		}

		inUseBullets.push_back(b);
		timeInterval = 0;

	}

}