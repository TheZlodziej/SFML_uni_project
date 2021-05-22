#include "HUD.h"

HUD::HUD(Entity* entity, TextureManager* textures):
	textures_(textures),
	entity_(entity),
	view_size_(sf::Vector2f(0.0f,0.0f))
{
	this->InitalizeHudElements();
	this->InitializeHudTextures();
}

HUD::~HUD()
{}

void HUD::InitializeHudTextures()
{
	this->hud_elements_.at(HUD_ELEMENT::HP).sprite.setTexture(this->textures_->Get(TEXTURE::HP_BAR));
	this->hud_elements_.at(HUD_ELEMENT::ITEM_BG).sprite.setTexture(this->textures_->Get(TEXTURE::ITEM_BG));
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).sprite.setTexture(this->textures_->Get(TEXTURE::SELECTED_ITEM));
}

void HUD::InitalizeHudElements()
{
	this->hud_elements_.insert({
		std::make_pair(HUD_ELEMENT::HP, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, -0.45f) }),
		std::make_pair(HUD_ELEMENT::ITEM_BG, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) }),
		std::make_pair(HUD_ELEMENT::SELECTED_ITEM, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) })
	});
}

void HUD::UpdatePosition(const float& delta_time)
{
	sf::Vector2f e_pos = this->entity_->GetPosition();

	for (auto& [key, el] : this->hud_elements_)
	{
		el.sprite.setPosition(e_pos + ScaleVec2f(this->view_size_, el.default_position) + el.current_offset);
	}

	//for(auto& el : this->items_placeholder_)
	//{
	//	el.sprite.setPosition(e_pos + ScaleVec2f(this->view_size_, el.default_position) + el.current_offset);
	//}
}

void HUD::UpdateHealthBar(const float& delta_time)
{
	this->hud_elements_.at(HUD_ELEMENT::HP).sprite.setScale(this->entity_->GetHp(), 1.0f);
}

void HUD::Update(const float& delta_time)
{
	this->UpdateHealthBar(delta_time);
	this->UpdateInventory(delta_time);
	this->UpdatePosition(delta_time);
}

void HUD::Draw(sf::RenderWindow& window)
{
	this->view_size_ = sf::Vector2f(window.getView().getSize());

	for (auto& [key,el] : this->hud_elements_)
	{
		window.draw(el.sprite);
	}

	/*for(auto& el : this->items_placeholder_)
	{
		window.draw(el.sprite);
	}*/

	this->entity_->GetInventory()->Draw(window);
}
