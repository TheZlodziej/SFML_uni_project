#include "Camera.h"

Camera::Camera():
	view_(sf::Vector2f(0.0f,0.0f), sf::Vector2f(GAME_CONST::CAMERA_WIDTH, GAME_CONST::CAMERA_HEIGHT))
{}

Camera::~Camera()
{

}

void Camera::Update(const sf::Vector2f& pos)
{
	this->view_.setCenter(pos);
}

sf::View& Camera::GetCamera()
{
	return this->view_;
}

void Camera::Attach(sf::RenderWindow& window)
{
	window.setView(this->view_);
}

void Camera::SetZoom(const float& zoom)
{
	this->view_.zoom(zoom);
}

void Camera::Resize(const sf::RenderWindow& window)
{
	float ratio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	this->view_.setSize(ratio * GAME_CONST::CAMERA_WIDTH, GAME_CONST::CAMERA_HEIGHT);
}