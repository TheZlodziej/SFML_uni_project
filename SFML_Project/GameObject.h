#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "TextureManager.h"

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

public:
	GameObject(const sf::Sprite& sprite, const GAME_OBJECT_TYPE& type, TextureManager& textures, const TEXTURE& texture=TEXTURE::DEFAULT);
	virtual ~GameObject();

	virtual void Update(const float& delta_time)=0;
	virtual void Draw(sf::RenderWindow& window)=0;
	sf::Vector2f GetPosition() const;
	Collider GetCollider();
};

