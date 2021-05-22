#pragma once

#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class HpBar
{
public:
	sf::RectangleShape bar;
	float hp;
	float max_hp;

	HpBar(const float& max_hp);
	void UpdatePosition(GameObject* relative_to);
	void UpdateSize();
	void Draw(sf::RenderWindow& window);
	void Update(GameObject* relative_to);
};

