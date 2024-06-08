#include "Bullet.h"

Engine::Bullet::Bullet(Sprite* sprite)
{
	this->sprite = sprite;
}

Engine::Bullet::~Bullet()
{
}

void Engine::Bullet::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::Bullet::GetPosition()
{
	return sprite->GetPosition();
}

void Engine::Bullet::Update(float deltaTime)
{
	float x = GetPosition().x;
	float y = GetPosition().y;

	// Update posisi berdasarkan direction
	if (direction == "up") {
		y += yVelocity * deltaTime;
		
	}
	else if (direction == "down") {
		y -= yVelocity * deltaTime;
	}
	else if (direction == "right") {
		x += xVelocity * deltaTime;
	}
	else if (direction == "left") {
		x -= xVelocity * deltaTime;
	}
	
	SetPosition(x, y);
	sprite->Update(deltaTime);
}

void Engine::Bullet::Draw()
{
	sprite->Draw();
}

void Engine::Bullet::SetDirection(string direction)
{
	this->direction = direction;

	// Atur rotasi atau skala sprite berdasarkan arah
	if (direction == "up") {
		sprite->SetRotation(90); // Rotasi 90 derajat
	}
	else if (direction == "down") {
		sprite->SetRotation(-90); // Rotasi -90 derajat
	}
	else if (direction == "right") {
		sprite->SetRotation(0); // Tidak ada rotasi
	}
	else if (direction == "left") {
		sprite->SetRotation(180); // Rotasi 180 derajat
	}
}
