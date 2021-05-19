#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	float range_; // range in which enemy can track the player
public:
	Enemy(const sf::Vector2f& position,
		TextureManager* textures,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ENEMY_1,
		const TEXTURE& texture = TEXTURE::ENEMY_1,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& strength = 10.0f,
		const float& hp = 1.0f,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& range = 150.0f);
	virtual ~Enemy();
	static Enemy* MakeEnemy(const sf::Vector2f& spawn_position, TextureManager* textures, const GAME_OBJECT_TYPE& type, const TEXTURE& texture);
	static Enemy* MakeRandomEnemy(const sf::Vector2f& spawn_position, TextureManager* textures);
	static std::pair<GAME_OBJECT_TYPE, TEXTURE> GetRandomEnemy();
	static float GetEnemyRange(const GAME_OBJECT_TYPE& type);
	static float GetEnemyStrength(const GAME_OBJECT_TYPE& type);
	static float GetEnemyHp(const GAME_OBJECT_TYPE& type);
};

