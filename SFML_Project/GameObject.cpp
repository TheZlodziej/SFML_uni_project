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
	return this->CollidingWith(object->sprite_);
}

bool GameObject::CollidingWith(const sf::Sprite sprite) const
{
	return this->CollidingWith(sprite.getGlobalBounds());
}

bool GameObject::CollidingWith(const sf::FloatRect rect) const
{
	sf::FloatRect rect_this = this->sprite_.getGlobalBounds();
	return rect_this.intersects(rect);
}

//bool GameObject::CircularCollision(const GameObject* object) const
//{
//	sf::Vector2f a_pos = this->sprite_.getPosition();
//	sf::Vector2f b_pos = object->sprite_.getPosition();
//	
//	sf::Vector2f a_scale = this->sprite_.getScale();
//	sf::Vector2f b_scale = object->sprite_.getScale();
//
//	sf::Vector2f a_tex_size = sf::Vector2f(this->sprite_.getTexture()->getSize());
//	sf::Vector2f b_tex_size = sf::Vector2f(object->sprite_.getTexture()->getSize());
//
//	a_tex_size.x *= a_scale.x;
//	a_tex_size.y *= a_scale.y;
//
//	b_tex_size.x *= b_scale.x;
//	b_tex_size.y *= b_scale.y;
//
//	float a_radius = std::min(a_tex_size.x, a_tex_size.y);
//	float b_radius = std::min(b_tex_size.x, b_tex_size.y);
//
//	float x_diff = a_pos.x - b_pos.x;
//	float y_diff = a_pos.y - b_pos.y;
//	float r_sum = 100.0f;//a_radius + b_radius;
//	
//	return x_diff * x_diff + y_diff * y_diff <= r_sum * r_sum;
//}