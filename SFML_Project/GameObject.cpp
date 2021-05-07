#include "GameObject.h"

GameObject::GameObject(const sf::Sprite& sprite):
	sprite_(sprite)
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

bool GameObject::CollidingWith(const GameObject* object) const
{
	sf::FloatRect rect_a = this->sprite_.getGlobalBounds();
	sf::FloatRect rect_b = object->sprite_.getGlobalBounds();
	return rect_a.intersects(rect_b);
}