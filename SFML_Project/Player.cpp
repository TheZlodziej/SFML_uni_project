#include "Player.h"

Player::Player(const sf::Sprite& sprite, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const float& strength):
	Entity(sprite, velocity, acceleration, strength)
{}

Player::~Player()
{}