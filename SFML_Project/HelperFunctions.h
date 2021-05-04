#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "GameConstants.h"

void ClampVector2f(sf::Vector2f& vec, const float& min, const float& max);
sf::Vector2f NormalizeVec2f(sf::Vector2f vec);	// returns negative unit vector to given vector