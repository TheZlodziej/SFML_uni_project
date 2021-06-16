#include "Inventory.h"
#include <iostream>
Inventory::Inventory():
	curr_item_idx_(0u),
	capacity_(6),
	view_size_(1.0f, 1.0f)
{
	using namespace GAME_CONST;

	this->items_bg_.setFillColor(ITEMS_BG_COLOR);
	this->items_bg_.setSize(sf::Vector2f(INVENTORY_ITEM_SIZE * this->capacity_, INVENTORY_ITEM_SIZE));
	this->items_bg_.setOrigin(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));

	this->selected_item_bg_.setFillColor(SELECTED_ITEM_COLOR);
	this->selected_item_bg_.setSize(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));
	this->selected_item_bg_.setOrigin(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));
}

Inventory::~Inventory()
{
	for (auto& item : this->items_)
	{
		delete item;
	}
}

void Inventory::Add(Item* item, sf::Font* font)
{
	if (this->items_.size() < this->capacity_)
	{
		this->items_.emplace_back(item);

		sf::Text text("", *font, 13u);
		text.setOutlineThickness(3.0f);
		text.setOutlineColor(sf::Color::Black);
		this->texts_.emplace_back(text);
	}
}

void Inventory::SetCurrentItemIdx(const int& item_index)
{
	if (item_index < 0)
	{
		this->curr_item_idx_ = static_cast<unsigned int>(this->capacity_ - 1);
	}
	else
	{
		this->curr_item_idx_ = static_cast<unsigned int>(item_index % this->capacity_);
	}
}

void Inventory::Remove(const unsigned int& item_idx)
{
	if (item_idx < this->items_.size())
	{
		auto item_it = this->items_.begin() + item_idx;
		delete* item_it;
		item_it = this->items_.erase(item_it);

		auto text_it = this->texts_.begin() + item_idx;
		text_it = this->texts_.erase(text_it);
	}
}

void Inventory::UpdateTexts()
{
	for (unsigned int i=0; i<this->items_.size(); i++)
	{
		auto it_dur_info = this->items_[i]->GetDurabilityInfo();

		std::string new_str = std::to_string(it_dur_info.second - it_dur_info.first) + "/" + std::to_string(it_dur_info.second);
		this->texts_[i].setString(new_str);
		
		// calculating new text position
		sf::FloatRect text_rect = this->texts_[i].getGlobalBounds();
		sf::Vector2f text_new_pos = this->items_[i]->GetIcon().getPosition();

		text_new_pos.x += GAME_CONST::INVENTORY_ITEM_SIZE / 2.0f - text_rect.width ;
		text_new_pos.y += GAME_CONST::INVENTORY_ITEM_SIZE / 2.0f - text_rect.height ;
		
		this->texts_[i].setPosition(text_new_pos);
	}
}

void Inventory::Draw(sf::RenderWindow& window)
{
	this->view_size_ = sf::Vector2f(window.getView().getSize());
	window.draw(this->items_bg_);
	window.draw(this->selected_item_bg_);

	for (unsigned int i = 0; i < this->GetCapacity(); i++)
	{
		if (i < this->GetSize())
		{
			sf::Sprite* sprite = &this->items_[i]->GetIcon();
			window.draw(*sprite);
			window.draw(this->texts_[i]);
		}
	}
}

unsigned int Inventory::GetCurrentItemIndex() const
{
	return this->curr_item_idx_;
}

unsigned int Inventory::GetCapacity() const
{
	return this->capacity_;
}

unsigned int Inventory::GetSize() const
{
	return this->items_.size();
}

std::vector<Item*> Inventory::GetItems()
{
	return this->items_;
}

Item* Inventory::GetCurrentItem()
{
	if (this->curr_item_idx_ < this->GetSize())
	{
		return this->items_[this->curr_item_idx_];
	}

	return nullptr;
}

void Inventory::SelectBestItem()
{
	unsigned int max_idx = 0;
	float max_pow = 0.0f;

	for (unsigned int i = 0; i < this->GetSize(); i++)
	{
		Item* it = this->items_[i];
		float it_pow = it->GetPower();

		if (it_pow > max_pow)
		{
			max_idx = i;
		}
	}

	this->SetCurrentItemIdx(max_idx);
}

void Inventory::Update(GameObject* relative_to, const float& delta_time)
{
	this->UpdateItems(delta_time);
	this->UpdatePosition(relative_to);
	this->UpdateTexts();
}

void Inventory::UpdateItems(const float& delta_time)
{
	for (auto& it : this->items_)
	{
		it->Update(delta_time);
	}
}

void Inventory::UpdatePosition(GameObject* relative_to)
{
	using namespace GAME_CONST;

	sf::Vector2f pos = relative_to->GetPosition();
	sf::Vector2f offset(INVENTORY_OFFSET_X, INVENTORY_OFFSET_Y);
	ScaleVec2f(offset, this->view_size_);

	this->items_bg_.setPosition(pos + offset);
	this->selected_item_bg_.setPosition(pos + offset + sf::Vector2f(INVENTORY_ITEM_SIZE * this->GetCurrentItemIndex(), 0.0f));

	for (unsigned int i = 0; i < this->GetSize(); i++)
	{
		sf::Sprite* it_icon = &this->items_[i]->GetIcon();
		float icon_offset_x = INVENTORY_OFFSET_X - INVENTORY_ITEM_SIZE * 0.5f + INVENTORY_ITEM_SIZE * i;
		float icon_offset_y = INVENTORY_OFFSET_Y - INVENTORY_ITEM_SIZE * 0.5f;
		sf::Vector2f icon_offset(icon_offset_x, icon_offset_y);
		ScaleVec2f(icon_offset, this->view_size_);

		it_icon->setPosition(pos+icon_offset);
	}
}
