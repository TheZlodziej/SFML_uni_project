#pragma once

#include "Entity.h"
#include <cmath>

class Player : public Entity
{
private:

public:
	Player(const sf::Vector2f& position,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::PLAYER,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& hp = GAME_CONST::PLAYER_HP,
		const float& push_back_force = 0.5f,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::PLAYER,
		const sf::Vector2u & animation_frames = sf::Vector2u(4, 2),
		const float& animation_time = .5f
		);
	virtual ~Player();
	void LookAtMouse(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) override;
};

