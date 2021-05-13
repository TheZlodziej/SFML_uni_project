#include "Entity.h"

Entity::Entity(const sf::Vector2f& position, TextureManager* textures, const TEXTURE& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const float& strength, const float& hp, const GAME_OBJECT_TYPE& type) :
	GameObject(position, type, textures, texture),
	velocity_(velocity),
	hp_(hp),
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
	this->UpdateAcceleration();
	this->UpdateVelocity(delta_time);
	this->ApplyDrag();
	this->Move();
}

void Entity::UpdateVelocity(const float& delta_time)
{
	this->velocity_ += this->acceleration_ * delta_time;
}

void Entity::ApplyDrag()
{
	this->velocity_ *= GAME_CONST::ENTITY_DRAG;
	ClampVec2f(this->velocity_, -GAME_CONST::MAX_ENTITY_VELOCITY, GAME_CONST::MAX_ENTITY_VELOCITY);
}

void Entity::UpdateAcceleration()
{
	ClampVec2f(this->acceleration_, -GAME_CONST::MAX_ENTITY_ACCELERATION, GAME_CONST::MAX_ENTITY_ACCELERATION);
}

void Entity::Move()
{
	this->sprite_.move(this->velocity_);
}

Inventory* Entity::GetInventory()
{
	return &this->inventory_;
}

void Entity::SetAcceleration(const sf::Vector2f& acceleration)
{
	this->acceleration_ = acceleration;
}

void Entity::Stop()
{
	this->acceleration_ = sf::Vector2f(0.0f, 0.0f);
	this->velocity_ = sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Entity::GetAcceleration() const 
{
	return this->acceleration_;
}

float Entity::GetHp() const
{
	return this->hp_;
}

void Entity::LoseHp(const float& percentage)
{
	this->hp_ -= percentage;
}

sf::Vector2f Entity::GetDirection(const Entity* entity) const
{
	return NormalizeVec2f(entity->sprite_.getPosition() - this->sprite_.getPosition());
}