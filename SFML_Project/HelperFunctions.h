#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "GameConstants.h"

void ClampVector2f(sf::Vector2f& vec, const float& min, const float& max);
sf::Vector2f GetDirection(const sf::Vector2f& vec);	// returns negative unit vector to given vector