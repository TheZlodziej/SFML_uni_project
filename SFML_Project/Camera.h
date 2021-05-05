#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "GameObject.h"

class Camera : public sf::View
{
private:

public:
	Camera();
	virtual ~Camera();
	void Update(const sf::Vector2f& pos);
	void Attach(sf::RenderWindow& window);
	void Resize(const sf::RenderWindow& window);
};

