#include "Entity.h"

Entity::Entity(const sf::Sprite& sprite, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const float& strength) :
	GameObject(sprite),
	velocity_(velocity),
	acceleration_(acceleration),
	strength_(strength)
{}

Entity::~Entity() {}

void Entity::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite_);
}

void Entity::Update(const float& delta_time)
{
	this->UpdateVelocity(delta_time);
	this->UpdateAcceleration(delta_time);
	this->Move(delta_time);
}

void Entity::UpdateVelocity(const float& delta_time)
{
	this->velocity_ += this->acceleration_ * delta_time;
}

void Entity::UpdateAcceleration(const float& delta_time)
{
	sf::Vector2f new_acceleration = this->acceleration_ - sf::Vector2f(10.0f, 10.0f) * delta_time;
	
	if (this->velocity_.x < 0.000001)
	{
		new_acceleration.x = 0.0f;
	}

	if (this->velocity_.y < 0.000001)
	{
		new_acceleration.y = 0.0f;
	}

	this->acceleration_ = new_acceleration;
}

void Entity::Move(const float& delta_time)
{
	this->sprite_.move(this->velocity_ * delta_time);
}

void Entity::AddToInventory(Item* item)
{
	this->inventory_.Add(item);
}

void Entity::RemoveFromInventory(const unsigned int& item_idx)
{
	this->inventory_.Remove(item_idx);
}

void Entity::SetAcceleration(const sf::Vector2f& new_acceleration)
{
	this->acceleration_ = new_acceleration;
}

sf::Vector2f Entity::GetAcceleration() const 
{
	return this->acceleration_;
}