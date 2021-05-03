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
	this->UpdateAcceleration(delta_time);
	this->UpdateVelocity(delta_time);
	this->Move(delta_time);
}

void Entity::UpdateVelocity(const float& delta_time)
{
	this->velocity_ += this->acceleration_ * delta_time;
	ClampVector2f(this->velocity_, -GAME_CONST::MAX_ENTITY_VELOCITY, GAME_CONST::MAX_ENTITY_VELOCITY);
}

void Entity::UpdateAcceleration(const float& delta_time)
{
	sf::Vector2f friction = delta_time * GetDirection(this->velocity_) * GAME_CONST::ENTITY_FRICTION;
	this->acceleration_ -= friction;
	ClampVector2f(this->acceleration_, -GAME_CONST::MAX_ENTITY_ACCELERATION, GAME_CONST::MAX_ENTITY_ACCELERATION);
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

void Entity::AddAcceleration(const sf::Vector2f& acceleration)
{
	this->acceleration_ += acceleration;
}

sf::Vector2f Entity::GetAcceleration() const 
{
	return this->acceleration_;
}