#include "Player.h"

Player::Player(const sf::Vector2f& position,
				TextureManager* textures,
				const TEXTURE& texture, 
				const sf::Vector2f& velocity, 
				const sf::Vector2f& acceleration, 
				const float& strength, 
				const float& hp,
				const GAME_OBJECT_TYPE& type,
				const sf::Vector2u& animation_frames,
				const float& animation_time):
	Entity(position, textures, texture, velocity, acceleration, strength, hp, type, animation_frames, animation_time)
{}

Player::~Player()
{}

void Player::LookAtMouse(const sf::RenderWindow& window)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2i player_pos = window.mapCoordsToPixel(this->sprite_.getPosition());

	float x_diff = static_cast<float>(mouse_pos.x) - static_cast<float>(player_pos.x);
	float y_diff = static_cast<float>(mouse_pos.y) - static_cast<float>(player_pos.y);

	float rot_angle = std::atan2(y_diff, x_diff) * 180.0f/GAME_CONST::PI; //converted to degrees
																	
	// add another 180 to match the argument list of setRotation
	// which is an angle between 0 and 360
	// but we also need to subtract 90 degrees so
	// the rotation of our sprite is correct

	this->sprite_.setRotation(rot_angle + 90.0f); 
}

void Player::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	this->inventory_.Draw(window);
}

void Player::Update(const float& delta_time)
{
	Entity::Update(delta_time);
	this->inventory_.Update(this, delta_time);
}
