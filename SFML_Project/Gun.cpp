#include "Gun.h"

Gun::Gun(const sf::Vector2f& position, 
	const int& durability, 
	TextureManager* textures,
	const float& cooldown,
	const TEXTURE& texture, 
	const GAME_OBJECT_TYPE& type, 
	const sf::Vector2u& animation_frames,
	const float& animation_time):
Item(position, durability, textures, cooldown, texture, type, animation_frames, animation_time)
{}

Gun::~Gun()
{}

void Gun::Use()
{
	if (this->CanUse())
	{
		this->time_after_use_ = 0.0f;
		// ... 
		std::cout << "boom\n";
		// ...
	}
}
