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
		std::make_pair(HUD_ELEMENT::SELECTED_ITEM, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) }),
		std::make_pair(HUD_ELEMENT::ITEM_0, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) }),
		std::make_pair(HUD_ELEMENT::ITEM_1, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(50.0f,  0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_2, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(100.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_3, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(150.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_4, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(200.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_5, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(250.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_6, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(300.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_7, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(350.0f, 0.0f)}),
		std::make_pair(HUD_ELEMENT::ITEM_8, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f), sf::Vector2f(400.0f, 0.0f)}),
	});
}

void HUD::UpdateInventory(Entity* entity)
{
	// items bg & selected items
	Inventory* inv = entity->GetInventory();

	unsigned int item_idx = inv->GetCurrentItemIndex();
	float new_x_position = 50.0f * item_idx;
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).current_offset.x = new_x_position;

	// items (depend on entity inventory)
	std::vector<Item*> items = entity->GetInventory()->GetItems();

	for (unsigned int i=0 ;i<items.size(); i++)
	{
		HUD_ELEMENT el = static_cast<HUD_ELEMENT>(static_cast<unsigned int>(HUD_ELEMENT::ITEM_0) + i);
		this->hud_elements_.at(el).sprite.setTexture(items[i]->GetTexture());
	}
}

void HUD::UpdatePosition(Entity* entity)
{
	sf::Vector2f e_pos = entity->GetPosition();

	for (auto& [key, el] : this->hud_elements_)
	{
		el.sprite.setPosition(e_pos + ScaleVec2f(this->view_size_, el.default_position) + el.current_offset);
	}
}

void HUD::UpdateHealthBar(Entity* entity)
{
	this->hud_elements_.at(HUD_ELEMENT::HP).sprite.setScale(entity->GetHp(), 1.0f);
}

void HUD::Update(Entity* entity)
{
	this->UpdateHealthBar(entity);
	this->UpdateInventory(entity);
	this->UpdatePosition(entity);
}

void HUD::Draw(sf::RenderWindow& window)
{
	this->view_size_ = sf::Vector2f(window.getView().getSize());

	for (auto& [key,el] : this->hud_elements_)
	{
		window.draw(el.sprite);
	}
}
