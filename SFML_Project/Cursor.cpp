#include "Cursor.h"

Cursor::Cursor():sprite_(sf::Sprite())
{
}

Cursor::~Cursor()
{
}

void Cursor::Init(TextureManager* textures, const TEXTURE& texture)
{
	this->sprite_.setTexture(textures->Get(TEXTURE::CURSOR));

	float half_w = this->sprite_.getGlobalBounds().width/2.0f;
	float half_h = this->sprite_.getGlobalBounds().height/2.0f;

	this->sprite_.setOrigin(half_w, half_h);
}

void Cursor::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite_);
}

void Cursor::Update(const sf::RenderWindow& window, const Camera& camera)
{
	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Vector2f win_size = static_cast<sf::Vector2f>(window.getSize());

	this->sprite_.setPosition(mouse_pos - win_size * 0.5f + camera.getCenter());
}
