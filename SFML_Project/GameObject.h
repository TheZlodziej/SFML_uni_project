#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "TextureManager.h"
#include "Animation.h"

enum class GAME_OBJECT_TYPE
{
	ENTITY,
	PLAYER,
	ENEMY,
	ITEM
};

class GameObject
{
protected:
	sf::Sprite sprite_;
	GAME_OBJECT_TYPE type_;
	TextureManager* textures_;
	TEXTURE texture_;
	Animation animation_;

public:
	GameObject(const sf::Vector2f& position,
			const GAME_OBJECT_TYPE& type, 
			TextureManager* textures, 
			const TEXTURE& texture = TEXTURE::DEFAULT, 
			const sf::Vector2u& animation_frames = { 1,1 }, 
			const float& animation_time=1.0f);
	virtual ~GameObject();

	virtual void Update(const float& delta_time);
	virtual void Draw(sf::RenderWindow& window)=0;
	sf::Vector2f GetPosition() const;
	Collider GetCollider();
	sf::Texture& GetTexture();
};

