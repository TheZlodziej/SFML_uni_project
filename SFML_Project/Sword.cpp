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
): Item(position, durability, textures, owner, cooldown, range, power, texture, type, animation_frames, animation_time, push_back_force),
animation_rotation_(0.0f),
animating_(false),
dealt_dmg_(false)
{
	float mid_x = this->sprite_.getGlobalBounds().width * 0.5f;
	float bottom_mid = this->sprite_.getGlobalBounds().height;

	this->sprite_.setOrigin(mid_x, bottom_mid);
}

Sword::~Sword()
{
}

void Sword::Use()
{
	if (!this->CanUse())
	{
		return;
	}
	
	this->uses_++;
	this->time_after_use_ = 0.0f;
	this->animating_ = true;
}

bool Sword::CheckCollision(GameObject* object)
{
	bool collision = this->sprite_.getGlobalBounds().intersects(object->GetSprite().getGlobalBounds());
	
	if (collision && !this->dealt_dmg_ && this->animating_)
	{
		this->dealt_dmg_ = true;
		return true;
	}

	return false;
}

void Sword::Update(const float& delta_time)
{
	if (!this->animating_)
	{
		this->dealt_dmg_ = false;
	}
	this->PutInHand();
	this->Animate(delta_time);
	Item::Update(delta_time);
}

bool Sword::CanUse() const
{
	if (!this->animating_)
	{
		return Item::CanUse();
	}

	return false;
}

void Sword::Animate(const float& delta_time)
{
	if (this->owner_ == nullptr)
	{
		return;
	}

	float owner_rot = this->owner_->GetSprite().getRotation();

	if (!this->animating_)
	{
		if (this->animation_rotation_ > 0.0f)
		{
			this->animation_rotation_ -= delta_time * GAME_CONST::SWORD_SPEED;
			this->sprite_.setRotation(-animation_rotation_ + owner_rot);
		}

		return;
	}

	this->animation_rotation_ += delta_time * GAME_CONST::SWORD_SPEED;
	this->sprite_.setRotation(-animation_rotation_ + owner_rot);

	if (this->animation_rotation_ >= GAME_CONST::SWORD_MAX_ROTATION)
	{
		this->animating_ = false;
	}
}
