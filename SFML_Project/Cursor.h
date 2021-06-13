#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Camera.h"

class Cursor
{
private:
	sf::Sprite sprite_;

public:
	Cursor();
	virtual ~Cursor();

	void Init(TextureManager* textures, const TEXTURE& texture);
	void Draw(sf::RenderWindow& window);
	void Update(const sf::RenderWindow& window, const Camera& camera); // window as an argument to get relative mouse position
	sf::Vector2f GetPosition();
};


