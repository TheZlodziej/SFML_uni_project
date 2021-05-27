#include "HelperFunctions.h"

void ClampVec2f(sf::Vector2f& vec, const float& min, const float& max)
{
	vec.x = std::clamp(vec.x, min, max);
	vec.y = std::clamp(vec.y, min, max);
}

void ClampFloat(float& num, const float& min, const float& max)
{
	num = std::clamp(num, min, max);
}

float DistanceVec2f(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b)
{
	float x_diff = vec_a.x - vec_b.x;
	float y_diff = vec_a.y - vec_b.y;

	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

sf::Vector2f ScaleVec2f(const sf::Vector2f& vec, const sf::Vector2f& scale)
{
	return sf::Vector2f(vec.x * scale.x, vec.y * scale.y);
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
	
	return 1.0f / LengthVec2f(vec) * vec;
}

float LengthVec2f(const sf::Vector2f& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}