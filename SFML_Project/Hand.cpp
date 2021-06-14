#include "Hand.h"

Hand::Hand(const sf::Vector2f& position, const unsigned int& durability, TextureManager* textures, GameObject* owner, const float& cooldown, const float& range, const float& power, const TEXTURE& texture, const GAME_OBJECT_TYPE& type, const sf::Vector2u& animation_frames, const float& animation_time, const float& push_back_force):
	Item(position, durability, textures, owner, cooldown, range, power, texture, type, animation_frames, animation_time, push_back_force),
	dealt_dmg_(false)
{
}

Hand::~Hand()
{
}

bool Hand::CheckCollision(GameObject* object)
{
	sf::Vector2f owner_pos = this->owner_->GetPosition();
	sf::Vector2f obj_pos = object->GetPosition();
	sf::Vector2f dist_vec = obj_pos - owner_pos;
	
	float dist = LengthVec2f(dist_vec);

	bool in_range = dist <= this->range_;

	if (in_range && !this->dealt_dmg_)
	{
		this->dealt_dmg_ = true;
		return true;
	}

	return false;
}

void Hand::Draw(sf::RenderWindow& window)
{
	// don't draw hand
	return;
}

void Hand::Use()
{
	if (this->CanUse())
	{
		this->time_after_use_ = 0.0f;
		this->dealt_dmg_ = false;
	}
}

