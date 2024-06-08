#include "Hero.h"

Engine::Hero::Hero(Texture* texture, Shader* shader, Quad* quad) :BaseCharacter(texture, shader, quad)
{
	sprite->SetNumXFrames(96);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("up", 0, 2);
	sprite->AddAnimation("upright", 12, 14);
	sprite->AddAnimation("right", 24, 26);
	sprite->AddAnimation("downright", 36, 38);
	sprite->AddAnimation("down", 48, 50);
	sprite->AddAnimation("downleft", 60, 62);
	sprite->AddAnimation("left", 72, 74);
	sprite->AddAnimation("upleft", 84, 86);
	sprite->PlayAnim("down");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(90);

	inputManager = NULL;
}

Engine::Hero::~Hero()
{
	
}

void Engine::Hero::Update(float deltaTime)
{
	if (Engine::CharacterState::ALIVE == state) {
		Move(deltaTime);
	}
}


void Engine::Hero::Move(float deltaTime)
{
	// Get Current Player's Position
	float speed = 0.9f;
	// s = v * t;
	// Control player's movement using keyboard or gamepad
	velocity = vec2(0, 0);
	vec2 oldPosition = GetPosition() + velocity * deltaTime;
	string anim = "";
	if (inputManager->IsKeyPressed("up")) {
		velocity += vec2(0.0f, speed);
		anim += "up";
		currentDirection = "up"; // Setel arah saat bergerak
	}

	if (inputManager->IsKeyPressed("down")) {
		velocity += vec2(0.0f, -speed);
		anim += "down";
		currentDirection = "down"; // Setel arah saat bergerak
	}

	if (inputManager->IsKeyPressed("walk-right")) {
		velocity += vec2(speed, 0.0f);
		anim += "right";
		currentDirection = "right"; // Setel arah saat bergerak
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		velocity += vec2(-speed, 0.0f);
		anim += "left";
		currentDirection = "left"; // Setel arah saat bergerak
	}

	if (inputManager->IsKeyPressed("attack")) {
		//anim += "attack";
	}
	
	// Update new player's position
	vec2 newPosition = GetPosition() + velocity * deltaTime;
	//if (newPosition.x < GetSprite()->GetScaleWidth() || newPosition.x > game->GetSettings()->screenWidth) {
	//	//newPosition = oldPosition;
	//}
	sprite->SetPosition(newPosition.x, newPosition.y);
	// Update player's animation
	sprite->PlayAnim(anim);
	sprite->Update(deltaTime);
}

void Engine::Hero::Init(Input* inputManager)
{
	this->inputManager = inputManager;

	inputManager->AddInputMapping("walk-left", SDLK_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_AXIS_LEFTX);

	inputManager->AddInputMapping("walk-right", SDLK_RIGHT);
	inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_AXIS_RIGHTX);

	inputManager->AddInputMapping("up", SDLK_UP);
	inputManager->AddInputMapping("walk-up", SDL_CONTROLLER_BUTTON_DPAD_UP);
	inputManager->AddInputMapping("walk-up", SDL_CONTROLLER_AXIS_RIGHTY);

	inputManager->AddInputMapping("down", SDLK_DOWN);
	inputManager->AddInputMapping("walk-down", SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	inputManager->AddInputMapping("walk-down", SDL_CONTROLLER_AXIS_LEFTY);

	inputManager->AddInputMapping("attack", SDLK_x);
}

string Engine::Hero::GetDirection()
{
	return currentDirection;
}