#include "HelperFunctions.h"

void ClampVector2f(sf::Vector2f& vec, const float& min, const float& max)
{
	float new_x = std::clamp(vec.x, min, max);
	float new_y = std::clamp(vec.y, min, max);
	
	vec.x = new_x;
	vec.y = new_y;
}