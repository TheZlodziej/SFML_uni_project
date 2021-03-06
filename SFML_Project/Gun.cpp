#include "Gun.h"

Gun::Gun(const sf::Vector2f& position, 
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
	const float& push_back_force):
Item(position, durability, textures, owner, cooldown, range, power, texture, type, animation_frames, animation_time, push_back_force)
{}

Gun::~Gun()
{}

void Gun::Use()
{
	if (!this->CanUse())
	{
		return;
	}

	this->uses_++;
	this->time_after_use_ = 0.0f;
		
	float owner_rot = DegToRad(this->owner_->GetSprite().getRotation());
	sf::Vector2f bullet_dir(std::sin(owner_rot),-std::cos(owner_rot));

	Bullet new_bullet(this->GetPosition(), GAME_OBJECT_TYPE::ITEM, this->textures_);
	new_bullet.SetVelocity(bullet_dir * GAME_CONST::BULLET_SPEED);
	new_bullet.GetSprite().setRotation(RadToDeg(owner_rot));
		
	this->bullets_.emplace_back(new_bullet);
}

bool Gun::CheckCollision(GameObject* object)
{
	Collider obj_collider = object->GetCollider();

	auto bullet = this->bullets_.begin();

	while (bullet != this->bullets_.end())
	{
		Collider bullet_collider = bullet->GetCollider();
		float pbf = object->GetPushBackForce();

		if (obj_collider.CheckCollision(bullet_collider, pbf))
		{
			bullet = this->bullets_.erase(bullet);
			return true;
		}
		else
		{
			++bullet;
		}
	}

	return false;
}

void Gun::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);

	// draw bullets
	for (auto& b : this->bullets_)
	{
		b.Draw(window);
	}
}

void Gun::Update(const float& delta_time)
{
	this->PutInHand();
	Item::Update(delta_time);

	// update bullets
	auto it = this->bullets_.begin();
	while (it != this->bullets_.end())
	{
	
		it->Update(delta_time);
		if (it->OutOfRange())
		{
			it = this->bullets_.erase(it);
		}
		else
		{
			++it;
		}
	}
}