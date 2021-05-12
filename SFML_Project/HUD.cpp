#include "HUD.h"

HUD::HUD(TextureManager* textures):
	textures_(textures)
{
	this->InitalizeHudElements();
	this->InitializeHudTextures();
}

HUD::~HUD()
{}

void HUD::InitializeHudTextures()
{
	this->hud_elements_.at(HUD_ELEMENT::HP).setTexture(this->textures_->Get(TEXTURE::HP_BAR));
}

void HUD::InitalizeHudElements()
{
	this->hud_elements_.insert(
		std::make_pair(HUD_ELEMENT::HP, this->textures_->Get(TEXTURE::HP_BAR))
	);
}

void HUD::Update(const Entity* entity)
{
	// health
	this->hud_elements_.at(HUD_ELEMENT::HP).setScale(entity->GetHp(), 1.0f);
	
	// items
	//this->_hud_elements.at(HUD_ELEMENT::ITEMS_BG);

	// position

	sf::Vector2f e_pos = entity->GetPosition();

	for (auto& [key,spr] : this->hud_elements_)
	{
		spr.setPosition(e_pos);
	}
}

void HUD::Draw(sf::RenderWindow& window)
{
	for (auto& [key,spr] : this->hud_elements_)
	{
		window.draw(spr);
	}
}
