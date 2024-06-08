#ifndef INGAMESCREEN_H
#define INGAMESCREEN_H

#include "Screen.h"
#include "ScreenManager.h"

#include "Enemy.h"
#include "Hero.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Text.h"

#include <random>

namespace Engine {
	class InGameScreen :
		public Engine::Screen
	{
	public:
		InGameScreen();
		void Init();
		void Update();
		void Draw();
	private:
		Texture* texture = NULL, *bulletTexture = NULL;
		vector<Enemy*> enemies; 
		vector<Bullet*> inUseBullets;
		vector<Bullet*> readyBullets;
		Hero* hero; 
		Sprite* backgroundSprite = NULL;
		Text* scoreText = NULL;
		Text* healthBarText = NULL;

		float spawnTimer;
		int enemyHits, totalScore, totalHealth;
		float yVelocity = 0, gravity = 0, timeInterval = 0, xBulletVel = 0;
		bool jump = false, toRight = true;

		void SpawnBullets();
	};
}

#endif