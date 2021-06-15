#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "GameConstants.h"

void ClampVec2f(sf::Vector2f& vec, const float& min, const float& max);					// keeps given vector between given minimum and maximum
void ClampFloat(float& num, const float& min, const float& max);						// clamps number in given range
float DistanceVec2f(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b);				// returns distance between 2 given vectors
float LengthVec2f(const sf::Vector2f& vec);												// returns length of vector
sf::Vector2f ScaleVec2f(const sf::Vector2f& vec, const sf::Vector2f& scale);			// scales given vector in x and y direction
sf::Vector2f NormalizeVec2f(sf::Vector2f vec);											// returns vector with length 1
float DegToRad(float deg);																// converts degrees to radians
float RadToDeg(float rad);																// converts radians to degrees
float Clamp(const float& num, const float& min, const float& max);						// works as standard clamp function
sf::Vector2f GetRandomVec2fInRange(const int& a, const sf::Vector2f& origin);			// gets random coordinate in (x,y) -> [-a; a]
