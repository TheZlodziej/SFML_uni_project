#include "Entity.h"

Entity::Entity(const sf::Vector2f& position, TextureManager* textures, const TEXTURE& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const float& hp, const float& push_back_force, const GAME_OBJECT_TYPE& type, const sf::Vector2u& animation_frames, const float& animation_time) :
	GameObject(position, type, textures, texture, push_back_force, animation_frames, animation_time),
	velocity_(velocity),
	hp_bar_(hp),
	acceleration_(acceleration)
{
	this->inventory_.Add(new Hand(sf::Vector2f(0.0f, 0.0f), 9999u, textures, this));
}

Entity::~Entity() {}

void Entity::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	this->hp_bar_.Draw(window);
	this->DrawItemInHand(window);
}

void Entity::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
	this->inventory_.Update(this, delta_time);
	this->UpdateAnimation();
	this->UpdateAcceleration();
	this->UpdateVelocity(delta_time);
	this->ApplyDrag();
	this->Move();
	this->hp_bar_.Update(this);
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

void Entity::UpdateAnimation()
{
	if (LengthVec2f(this->velocity_) <= GAME_CONST::FLOAT_PRECISION)
	{
		this->animation_.UpdateState(ANIMATION_STATE::IDLE);
	}
	else
	{
		this->animation_.UpdateState(ANIMATION_STATE::WALK);
	}
}

void Entity::Move()
{
	this->sprite_.move(this->velocity_);
}

void Entity::DrawItemInHand(sf::RenderWindow& window)
{
	Item* it = this->inventory_.GetCurrentItem();
	
	if (it != nullptr)
	{
		it->Draw(window);
	};
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

void Entity::UseItem()
{
	Item* it = this->inventory_.GetCurrentItem();

	if (it != nullptr)
	{
		it->Use();
	}
}

sf::Vector2f Entity::GetAcceleration() const 
{
	return this->acceleration_;
}

bool Entity::LoseHp(const float& amount)
{
	float new_hp = this->hp_bar_.hp - amount;

	if (new_hp > 0.0f)
	{
		this->hp_bar_.hp = new_hp;
	}
	else
	{
		return false;
	}

	ClampFloat(this->hp_bar_.hp, 0.0f, this->hp_bar_.max_hp);
	return true;
}

void Entity::LookAt(GameObject* object)
{
	sf::Vector2f object_pos = object->GetSprite().getPosition() - this->sprite_.getPosition();
	float angle = RadToDeg(std::atan2(object_pos.y, object_pos.x));
	this->sprite_.setRotation(angle + 90.0f);
}

sf::Vector2f Entity::GetDirection(const Entity* entity) const
{
	return NormalizeVec2f(entity->sprite_.getPosition() - this->sprite_.getPosition());
}