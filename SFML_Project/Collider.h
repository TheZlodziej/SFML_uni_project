#pragma once

#include <SFML/Graphics.hpp>
#include "HelperFunctions.h"
#include <cmath>

class Collider
{
private:
	sf::Sprite& sprite_;
public:
	Collider(sf::Sprite& sprite);
	virtual ~Collider();
	void Move(sf::Vector2f direction);
	bool CheckCollision(Collider& obj, float back_force);	// circual collision (dx^2 + dy^2 <= r^2)
};

