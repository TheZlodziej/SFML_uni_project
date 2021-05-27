#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const GAME_OBJECT_TYPE& type, TextureManager* textures, const TEXTURE& texture, const float& max_distance, const float& push_back_force, const sf::Vector2u& animation_frames, const float& animation_time):
	GameObject(position, type, textures, texture, push_back_force, animation_frames, animation_time),
	velocity_(sf::Vector2f(0.0f,0.0f)),
	distance_traveled_(0.0f),
	max_distance_(max_distance)
{}

Bullet::~Bullet()
{}

void Bullet::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
	this->sprite_.move(this->velocity_ * delta_time);
	this->distance_traveled_ += LengthVec2f(this->velocity_ * delta_time);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Bullet::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity_ = velocity;
}

bool Bullet::OutOfRange() const
{
	return this->distance_traveled_ >= max_distance_;
}
