#include "HelperFunctions.h"

void ClampVector2f(sf::Vector2f& vec, const float& min, const float& max)
{
	vec.x = std::clamp(vec.x, min, max);
	vec.y = std::clamp(vec.y, min, max);
}

sf::Vector2f NormalizeVec2f(sf::Vector2f vec)
{
	if (std::abs(vec.x) <= GAME_CONST::FLOAT_PRECISION)
	{
		vec.x = 0.0f;
	}

	if (std::abs(vec.y) <= GAME_CONST::FLOAT_PRECISION)
	{
		vec.y = 0.0f;
	}

	if (vec == sf::Vector2f(0.0f, 0.0f))
	{
		return vec;
	}
	
	float vec_len = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	return 1.0f / vec_len * vec;

	//// normalize length
	//float vec_len = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	//if (vec_len <= GAME_CONST::FLOAT_PRECISION)
	//{
	//	return sf::Vector2f(0.0f,0.0f);
	//}
	//return 1.0f/vec_len * ret;
	//return ret;
}