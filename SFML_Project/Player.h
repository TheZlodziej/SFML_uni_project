#pragma once

#include "Entity.h"
#include <cmath>

class Player : public Entity
{
private:

public:
	Player(const sf::Sprite& sprite,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& strength = 10.0f,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::PLAYER
		);
	virtual ~Player();
	void LookAtMouse(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) override;
};

