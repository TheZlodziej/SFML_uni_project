#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	sf::Vector2f velocity_; // no acceleration because we don't want the bullet to slow down so it's not needed
	float distance_traveled_;
	float max_distance_;

public:
	Bullet( const sf::Vector2f& position,
		const GAME_OBJECT_TYPE& type,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::BULLET,
		const float& max_distance = 1000.0f,
		const float& push_back_force = 0.5f,
		const sf::Vector2u& animation_frames = { 1,1 },
		const float& animation_time = 1.0f);
	virtual ~Bullet();

	virtual void Update(const float& delta_time) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void SetVelocity(const sf::Vector2f& velocity);
};

