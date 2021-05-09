// this call was made based on this tutorial
// https://www.youtube.com/watch?v=l2iCYCLi6MU&ab_channel=HilzeVonck

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
	bool CheckCollision(Collider& obj, float back_force);
};

