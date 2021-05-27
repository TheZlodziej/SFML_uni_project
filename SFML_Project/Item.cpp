#include "Item.h"

Item::Item(const sf::Vector2f& position,
			const unsigned int& durability, 
			TextureManager* textures,
			GameObject* owner,
			const float& cooldown,
			const TEXTURE& texture,
			const GAME_OBJECT_TYPE& type,
			const sf::Vector2u& animation_frames,
			const float& animation_time,
			const float& push_back_force):
	GameObject(position, type, textures, texture, push_back_force, animation_frames, animation_time),
	owner_(owner),
	uses_(0u),
	durability_(durability),
	time_after_use_(cooldown),
	cooldown_time_(cooldown)
{}

Item::~Item()
{}

bool Item::CanUse() const
{
	return this->time_after_use_ >= this->cooldown_time_ 
		&& this->HasOwner()
		&& this-> uses_ < this->durability_;
}

void Item::SetOwner(GameObject* entity)
{
	this->owner_ = entity;
}

void Item::RemoveOwner()
{
	this->owner_ = nullptr;
}

bool Item::HasOwner() const
{
	return this->owner_ != nullptr;
}

void Item::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Item::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
	this->time_after_use_ += delta_time;
}