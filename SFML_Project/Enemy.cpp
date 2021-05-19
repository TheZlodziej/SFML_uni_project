#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, TextureManager* textures, const GAME_OBJECT_TYPE& type, const TEXTURE& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const float& strength, const float& hp, const sf::Vector2u& animation_frames, const float& animation_time, const float& range) :
	Entity(position, textures, texture, velocity, acceleration, strength, hp, type, animation_frames, animation_time),
	range_(range)
{}

Enemy::~Enemy()
{
}

Enemy* Enemy::MakeEnemy(const sf::Vector2f& spawn_position, TextureManager* textures, const GAME_OBJECT_TYPE& type, const TEXTURE& texture)
{
	return new Enemy(
		spawn_position,
		textures, type, 
		texture, 
		sf::Vector2f(0.0f,0.0f), 
		sf::Vector2f(0.0f, 0.0f), 
		Enemy::GetEnemyStrength(type),
		Enemy::GetEnemyHp(type),
		sf::Vector2u(1,1),
		1.0f,
		Enemy::GetEnemyRange(type)
	);
}

Enemy* Enemy::MakeRandomEnemy(const sf::Vector2f& spawn_position, TextureManager* textures)
{
	std::pair<GAME_OBJECT_TYPE, TEXTURE> random_enemy = Enemy::GetRandomEnemy();
	return MakeEnemy(spawn_position, textures, random_enemy.first, random_enemy.second);
}

std::pair<GAME_OBJECT_TYPE, TEXTURE> Enemy::GetRandomEnemy()
{
	unsigned int random_num = std::rand()%3; // random uint mod num of enemy types
	
	switch (random_num)
	{
	case 0:
		return std::make_pair(GAME_OBJECT_TYPE::ENEMY_0, TEXTURE::ENEMY_0);
	case 1:
		return std::make_pair(GAME_OBJECT_TYPE::ENEMY_1, TEXTURE::ENEMY_1);
	case 2:
		return std::make_pair(GAME_OBJECT_TYPE::ENEMY_2, TEXTURE::ENEMY_2);
	default:
		return std::make_pair(GAME_OBJECT_TYPE::ENEMY_0, TEXTURE::ENEMY_0);
	}
}

float Enemy::GetEnemyRange(const GAME_OBJECT_TYPE& type)
{
	switch (type)
	{
	case GAME_OBJECT_TYPE::ENEMY_0:
		return GAME_CONST::ENEMY_RANGE[0];

	case GAME_OBJECT_TYPE::ENEMY_1:
		return GAME_CONST::ENEMY_RANGE[1];

	case GAME_OBJECT_TYPE::ENEMY_2:
		return GAME_CONST::ENEMY_RANGE[2];

	default:
		return GAME_CONST::ENEMY_RANGE[0];
	}
}

float Enemy::GetEnemyStrength(const GAME_OBJECT_TYPE& type)
{
	switch (type)
	{
	case GAME_OBJECT_TYPE::ENEMY_0:
		return GAME_CONST::ENEMY_STRENGTH[0];

	case GAME_OBJECT_TYPE::ENEMY_1:
		return GAME_CONST::ENEMY_STRENGTH[1];

	case GAME_OBJECT_TYPE::ENEMY_2:
		return GAME_CONST::ENEMY_STRENGTH[2];

	default:
		return GAME_CONST::ENEMY_STRENGTH[0];
	}
}

float Enemy::GetEnemyHp(const GAME_OBJECT_TYPE& type)
{
	switch (type)
	{
	case GAME_OBJECT_TYPE::ENEMY_0:
		return GAME_CONST::ENEMY_HP[0];

	case GAME_OBJECT_TYPE::ENEMY_1:
		return GAME_CONST::ENEMY_HP[1];

	case GAME_OBJECT_TYPE::ENEMY_2:
		return GAME_CONST::ENEMY_HP[2];

	default:
		return GAME_CONST::ENEMY_HP[0];
	}
}
