#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "GameConstants.h"

void ClampVec2f(sf::Vector2f& vec, const float& min, const float& max);		// keeps given vector between given minimum and maximum
float DistanceVec2f(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b);	// returns distance between 2 given vectors
sf::Vector2f NormalizeVec2f(sf::Vector2f vec);								// returns negative unit vector to given vector