#include "Item.h"

Item::Item(const sf::Vector2f& position,
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
	GameObject(position, type, textures, texture, push_back_force, animation_frames, animation_time),
	owner_(owner),
	uses_(0u),
	durability_(durability),
	time_after_use_(cooldown),
	cooldown_time_(cooldown),
	icon_(sprite_),
	range_(range),
	power_(power)
{
	//setup icon so it's correct size
	sf::FloatRect icon_rect = this->icon_.getGlobalBounds();
	sf::Vector2f icon_size(icon_rect.width, icon_rect.height);
	float icon_ratio = icon_size.x / icon_size.y;
	sf::Vector2f icon_scale(GAME_CONST::INVENTORY_ITEM_SIZE / icon_size.x * icon_ratio, GAME_CONST::INVENTORY_ITEM_SIZE / icon_size.y);
	this->icon_.setScale(icon_scale);
}

Item::~Item()
{}

bool Item::CanUse() const
{
	return this->time_after_use_ >= this->cooldown_time_ 
		&& this->HasOwner()
		&& this-> uses_ < this->durability_;
}

void Item::SetOwner(GameObject* entity)
{
	this->owner_ = entity;
}

void Item::RemoveOwner()
{
	this->owner_ = nullptr;
}

void Item::UpdateIcon()
{
	this->icon_.setTextureRect(this->sprite_.getTextureRect());
}

sf::Sprite& Item::GetIcon()
{
	return this->icon_;
}

float Item::GetRange() const
{
	return this->range_;
}

bool Item::HasOwner() const
{
	return this->owner_ != nullptr;
}

float Item::GetPower() const
{
	return this->power_;
}

void Item::PutInHand()
{
	if (this->owner_ == nullptr)
	{
		return;
	}

	sf::IntRect owner_size = this->owner_->GetSprite().getTextureRect();
	float half_o_w = static_cast<float>(owner_size.width) * 0.5f;

	sf::Vector2f owner_pos = this->owner_->GetPosition();

	sf::Vector2f hand_pos = owner_pos;
	hand_pos.x += half_o_w;

	float half_i_h = static_cast<float>(this->sprite_.getTextureRect().height) * 0.5f;

	float owner_rot = DegToRad(this->owner_->GetSprite().getRotation());
	sf::Vector2f item_pos(
		std::cos(owner_rot) * (hand_pos.x - owner_pos.x) - std::sin(owner_rot) * (hand_pos.y - owner_pos.y),
		std::sin(owner_rot) * (hand_pos.x - owner_pos.x) + std::cos(owner_rot) * (hand_pos.y - owner_pos.y)
	);

	this->sprite_.setPosition(owner_pos + item_pos);
	this->sprite_.setRotation(RadToDeg(owner_rot));
}

void Item::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Item::Update(const float& delta_time)
{
	GameObject::Update(delta_time);
	this->UpdateIcon();
	this->time_after_use_ += delta_time;
}