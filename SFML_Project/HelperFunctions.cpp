#include "HelperFunctions.h"

void ClampVector2f(sf::Vector2f& vec, const float& min, const float& max)
{
	vec.x = std::clamp(vec.x, min, max);
	vec.y = std::clamp(vec.y, min, max);
}

sf::Vector2f GetDirection(const sf::Vector2f& vec)
{
	sf::Vector2f ret(0.0f, 0.0f);

	// x dir
 	if (vec.x > GAME_CONST::FLOAT_PRECISION)
	{
		ret.x = -1.0f;
	}
	else if (vec.x < -GAME_CONST::FLOAT_PRECISION)
	{
		ret.x = 1.0f;
	}

	// y dir
	if (vec.y > GAME_CONST::FLOAT_PRECISION)
	{
		ret.y = -1.0f;
	}
	else if (vec.y < -GAME_CONST::FLOAT_PRECISION)
	{
		ret.y = 1.0f;
	}

	return ret;
}