#include "HUD.h"

HUD::HUD()
{
	this->InitializeHudTextures();
	this->InitalizeHudElements();
}

HUD::~HUD()
{}

void HUD::InitializeHudTextures()
{
	//this->_textures.Add();
}

void HUD::InitalizeHudElements()
{
	sf::Sprite hp_bar;
	this->_hud_elements.emplace_back();
}

void HUD::Update(const Entity* entity)
{
	sf::Vector2f offset = entity->GetPosition();

	for (auto& el : this->_hud_elements)
	{
		el.move(offset);
	}
}

void HUD::Draw(sf::RenderWindow& window)
{
	for (auto& el : this->_hud_elements)
	{
		window.draw(el);
	}
}
