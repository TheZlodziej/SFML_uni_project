#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "TextureManager.h"
#include "Animation.h"

enum class GAME_OBJECT_TYPE
{
	ENTITY,
	PLAYER,
	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	ITEM,
	TERRAIN
};

class GameObject
{
protected:
	sf::Sprite sprite_;
	GAME_OBJECT_TYPE type_;
	TextureManager* textures_;
	TEXTURE texture_;
	Animation animation_;
	float push_back_force_;

public:
	GameObject(const sf::Vector2f& position,
			const GAME_OBJECT_TYPE& type, 
			TextureManager* textures, 
			const TEXTURE& texture = TEXTURE::DEFAULT,
			const float& push_back_force = 0.5f,
			const sf::Vector2u& animation_frames = { 1,1 }, 
			const float& animation_time=1.0f);
	virtual ~GameObject();

	virtual void Update(const float& delta_time);
	virtual void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	Collider GetCollider();
	sf::Texture& GetTexture();
	sf::Sprite& GetSprite();
	GAME_OBJECT_TYPE GetType() const;
	float GetPushBackForce() const;

	static bool IsEntity(const GameObject* object);
};

