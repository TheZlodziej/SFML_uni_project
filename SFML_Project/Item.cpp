#include "Item.h"

Item::Item(const sf::Vector2f& position, 
			const int& durability, 
			TextureManager* textures, 
			const TEXTURE& texture, 
			const GAME_OBJECT_TYPE& type,
			const sf::Vector2u& animation_frames,
			const float& animation_time):
	GameObject(position, type, textures, texture, animation_frames, animation_time),
	durability_(durability)
{}

Item::~Item()
{}

void Item::Draw(sf::RenderWindow& window)
{
	
}

void Item::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
}