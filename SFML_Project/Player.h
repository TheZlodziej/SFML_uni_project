#pragma once

#include "Entity.h"
#include "HUD.h"
#include <cmath>

class Player : public Entity
{
private:
	HUD hud_;
public:
	Player(const sf::Vector2f& position,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::PLAYER,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& strength = 10.0f,
		const float& hp = 1.0f,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::PLAYER,
		const sf::Vector2u & animation_frames = sf::Vector2u(4, 1),
		const float& animation_time = .5f
		);
	virtual ~Player();
	void LookAtMouse(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) override;
	void Update(const float& delta_time) override;
};

