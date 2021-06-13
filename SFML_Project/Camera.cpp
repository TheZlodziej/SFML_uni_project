#include "Camera.h"

Camera::Camera():
	sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(GAME_CONST::CAMERA_WIDTH, GAME_CONST::CAMERA_HEIGHT))
{}

Camera::~Camera()
{

}

void Camera::Update(const sf::Vector2f& pos)
{
	this->setCenter(pos);
}

void Camera::Attach(sf::RenderWindow& window)
{
	window.setView(static_cast<sf::View>(*this));
}

void Camera::Resize(const sf::RenderWindow& window)
{
	using namespace GAME_CONST;
	float x_ratio = static_cast<float>(window.getSize().x) / CAMERA_WIDTH;
	float y_ratio = static_cast<float>(window.getSize().y) / CAMERA_HEIGHT;
	
	this->setSize(sf::Vector2f(x_ratio * CAMERA_WIDTH, y_ratio * CAMERA_HEIGHT) * CAMERA_ZOOM);
}