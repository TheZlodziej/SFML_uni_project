#include "Item.h"

Item::Item(const sf::Vector2f& position, 
			const int& durability, 
			TextureManager* textures,
			const float& cooldown,
			const TEXTURE& texture, 
			const GAME_OBJECT_TYPE& type,
			const sf::Vector2u& animation_frames,
			const float& animation_time):
	GameObject(position, type, textures, texture, animation_frames, animation_time),
	durability_(durability),
	time_after_use_(cooldown),
	cooldown_time_(cooldown)
{}

Item::~Item()
{}

bool Item::CanUse() const
{
	return this->time_after_use_ >= this->cooldown_time_;
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite_);
}

void Item::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
	this->time_after_use_ += delta_time;
}