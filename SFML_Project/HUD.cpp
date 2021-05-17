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
	this->hud_elements_.at(HUD_ELEMENT::ITEM_BG).sprite.setTexture(this->textures_->Get(TEXTURE::ITEM_BG));
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).sprite.setTexture(this->textures_->Get(TEXTURE::SELECTED_ITEM));
}

void HUD::InsertItems(Entity* entity, const float& item_box_width, const sf::Vector2f& inventory_scale)
{
	this->items_placeholder_.clear();
	std::vector<Item*> items = entity->GetInventory()->GetItems();
	for (unsigned int i=0; i<items.size(); i++)
	{
		this->items_placeholder_.emplace_back(
			HudElement
			{
				sf::Sprite(),
				this->hud_elements_.at(HUD_ELEMENT::ITEM_BG).default_position,
				sf::Vector2f(static_cast<float>(i) * item_box_width / inventory_scale.x, 0.0f)
			}
		);
	}
}

void HUD::InitalizeHudElements()
{
	this->hud_elements_.insert({
		std::make_pair(HUD_ELEMENT::HP, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, -0.45f) }),
		std::make_pair(HUD_ELEMENT::ITEM_BG, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) }),
		std::make_pair(HUD_ELEMENT::SELECTED_ITEM, HudElement{ sf::Sprite(), sf::Vector2f(-0.45f, 0.4f) })
	});
}

void HUD::UpdateInventory(Entity* entity)
{
	// items bg & selected items
	Inventory* inv = entity->GetInventory();
	float inv_size = static_cast<float>(inv->GetSize());
	sf::Vector2f inv_scale(inv_size, 1.0f);
	unsigned int item_idx = inv->GetCurrentItemIndex();
	float item_box_width = this->hud_elements_.at(HUD_ELEMENT::ITEM_BG).sprite.getGlobalBounds().width;
	float new_x_position = item_box_width * item_idx;

	this->hud_elements_.at(HUD_ELEMENT::ITEM_BG).sprite.setScale(inv_scale);
	this->hud_elements_.at(HUD_ELEMENT::SELECTED_ITEM).current_offset.x = new_x_position / inv_scale.x;

	// items (depend on entity inventory)
	std::vector<Item*> items = entity->GetInventory()->GetItems();

	if (this->items_placeholder_.size() != items.size())
	{
		InsertItems(entity, item_box_width, inv_scale);
	}

	for (unsigned int i=0 ;i<items.size(); i++)
	{
		this->items_placeholder_[i].sprite.setTexture(items[i]->GetTexture());
	}
}

void HUD::UpdatePosition(Entity* entity)
{
	sf::Vector2f e_pos = entity->GetPosition();

	for (auto& [key, el] : this->hud_elements_)
	{
		el.sprite.setPosition(e_pos + ScaleVec2f(this->view_size_, el.default_position) + el.current_offset);
	}

	for(auto& el : this->items_placeholder_)
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

	for(auto& el : this->items_placeholder_)
	{
		window.draw(el.sprite);
	}
}
