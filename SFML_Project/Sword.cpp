#include "Sword.h"

Sword::Sword(const sf::Vector2f& position, 
	const unsigned int& durability, 
	TextureManager* textures, 
	GameObject* owner, 
	const float& cooldown, 
	const float& range, 
	const float& power, 
	const TEXTURE& texture, 
	const GAME_OBJECT_TYPE& type, 
	const sf::Vector2u& animation_frames, 
	const float& animation_time, 
	const float& push_back_force
): Item(position, durability, textures, owner, cooldown, range, power, texture, type, animation_frames, animation_time, push_back_force)
{}

Sword::~Sword()
{
}

void Sword::Use()
{
}

bool Sword::CheckCollision(GameObject* object)
{
	return false;
}

void Sword::Draw(sf::RenderWindow& window)
{
}

void Sword::Update(const float& delta_time)
{
}
