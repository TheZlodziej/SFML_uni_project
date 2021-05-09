#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

class GameObject
{
protected:
	sf::Sprite sprite_;

public:
	GameObject(const sf::Sprite& sprite);
	virtual ~GameObject();

	virtual void Update(const float& delta_time)=0;
	virtual void Draw(sf::RenderWindow& window)=0;
	sf::Vector2f GetPosition() const;
	Collider GetCollider();
};

