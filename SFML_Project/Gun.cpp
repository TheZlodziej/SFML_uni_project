#include "Gun.h"

Gun::Gun(const sf::Vector2f& position, 
	const int& durability, 
	TextureManager* textures, 
	const TEXTURE& texture, 
	const GAME_OBJECT_TYPE& type, 
	const sf::Vector2u& animation_frames,
	const float& animation_time):
Item(position, durability, textures, texture, type, animation_frames, animation_time)
{}

Gun::~Gun()
{}

void Gun::Use()
{
}
