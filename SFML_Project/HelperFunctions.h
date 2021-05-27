#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "GameConstants.h"

void ClampVec2f(sf::Vector2f& vec, const float& min, const float& max);		// keeps given vector between given minimum and maximum
void ClampFloat(float& num, const float& min, const float& max);
float DistanceVec2f(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b);	// returns distance between 2 given vectors
float LengthVec2f(const sf::Vector2f& vec);									// returns length of vector
sf::Vector2f ScaleVec2f(const sf::Vector2f& vec, const sf::Vector2f& scale);// scales given vector in x and y direction
sf::Vector2f NormalizeVec2f(sf::Vector2f vec);								// returns negative unit vector to given vector