#include "HUD.h"

HUD::HUD(TextureManager* textures):
	textures_(textures),
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
	this->hud_elements_.at(HUD_ELEMENT::ITEMS_BG).sprite.setTexture(this->textures_->Get(TEXTURE::ITEMS_BG));
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).sprite.setTexture(this->textures_->Get(TEXTURE::SELECTED_ITEM));
}

void HUD::InitalizeHudElements()
{
	this->hud_elements_.insert({
		std::make_pair(HUD_ELEMENT::HP, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, -0.45f) }),
		std::make_pair(HUD_ELEMENT::ITEMS_BG, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) }),
		std::make_pair(HUD_ELEMENT::SELECTED_ITEM, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) })
	});
}

void HUD::Update(Entity* entity)
{
	// health
	this->hud_elements_.at(HUD_ELEMENT::HP).sprite.setScale(entity->GetHp(), 1.0f);
	
	// items (current item selection)
	unsigned int item_idx = entity->GetInventory()->GetCurrentItemIndex();
	float new_x_position = 50.0f * item_idx;
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).current_offset.x = new_x_position;

	// transform position
	sf::Vector2f e_pos = entity->GetPosition();

	for (auto& [key,el] : this->hud_elements_)
	{
		el.sprite.setPosition(e_pos + ScaleVec2f(this->view_size_, el.default_position) + el.current_offset);
	}
}

void HUD::Draw(sf::RenderWindow& window)
{
	this->view_size_ = sf::Vector2f(window.getView().getSize());

	for (auto& [key,el] : this->hud_elements_)
	{
		window.draw(el.sprite);
	}
}
