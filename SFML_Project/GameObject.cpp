#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& position, const GAME_OBJECT_TYPE& type, TextureManager* textures, const TEXTURE& texture, const sf::Vector2u& animation_frames, const float& animation_time):
	sprite_(sf::Sprite()),
	type_(type),
	textures_(textures),
	texture_(texture),
	animation_(textures->Get(texture), animation_frames, animation_time)
{
	this->sprite_.setPosition(position);

	//set texture to default
	this->sprite_.setTexture(textures->Get(texture));
	this->sprite_.setTextureRect(this->animation_.GetFrameRect());

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

void GameObject::Update(const float& delta_time)
{
	this->animation_.Update(delta_time);
	this->sprite_.setTextureRect(this->animation_.GetFrameRect());
}

sf::Texture& GameObject::GetTexture()
{
	return this->textures_->Get(this->texture_);
}

float GameObject::GetRadius() const
{
	sf::FloatRect pos_rect = this->sprite_.getGlobalBounds();
	float r = std::sqrt(pos_rect.width * pos_rect.width + pos_rect.height * pos_rect.height) * 0.5f;
	return r;
}

sf::Sprite& GameObject::GetSprite()
{
	return this->sprite_;
}
