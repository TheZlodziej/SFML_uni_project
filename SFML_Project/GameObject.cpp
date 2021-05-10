#include "GameObject.h"

GameObject::GameObject(const sf::Sprite& sprite, const GAME_OBJECT_TYPE& type):
	sprite_(sprite),
	type_(type)
{
	//set origin of the entity to center
	float mid_point_x = this->sprite_.getLocalBounds().width / 2.0f;
	float mid_point_y = this->sprite_.getLocalBounds().height / 2.0f;

	this->sprite_.setOrigin(mid_point_x, mid_point_y);
}

GameObject::~GameObject()
{
}

sf::Vector2f GameObject::GetPosition() const
{
	return this->sprite_.getPosition();
}

Collider GameObject::GetCollider()
{
	return Collider(this->sprite_);
}