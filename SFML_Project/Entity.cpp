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
	this->ApplyDrag(delta_time);
	this->velocity_ += this->acceleration_ * delta_time;
	ClampVector2f(this->velocity_, -GAME_CONST::MAX_ENTITY_VELOCITY, GAME_CONST::MAX_ENTITY_VELOCITY);
}

void Entity::ApplyDrag(const float& delta_time)
{
	this->velocity_ *= GAME_CONST::ENTITY_DRAG;
}

void Entity::UpdateAcceleration(const float& delta_time)
{
	//std::cout << this->acceleration_.x << " " << this->acceleration_.y << "\n";
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

void Entity::SetAcceleration(const sf::Vector2f& acceleration)
{
	this->acceleration_ = acceleration;
}

sf::Vector2f Entity::GetAcceleration() const 
{
	return this->acceleration_;
}

sf::Vector2f Entity::GetDirection(const Entity* entity) const
{
	return GetVector2fDir(entity->sprite_.getPosition() - this->sprite_.getPosition());
}