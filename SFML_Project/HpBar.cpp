#include "HpBar.h"

HpBar::HpBar(const float& max_hp) :
	hp(max_hp),
	max_hp(max_hp)
{
	using namespace GAME_CONST;

	this->bar.setOrigin(static_cast<float>(HP_BAR_WIDTH) * 0.5f, static_cast<float>(HP_BAR_HEIGHT) * 0.5f);
	this->bar.setSize(sf::Vector2f(HP_BAR_WIDTH, HP_BAR_HEIGHT));
	this->bar.setFillColor(sf::Color(HP_BAR_R, HP_BAR_G, HP_BAR_B));

	this->bar_bg.setOrigin(this->bar.getOrigin());
	this->bar_bg.setSize(this->bar.getSize());
	this->bar_bg.setFillColor(sf::Color(26,26,26));
}

void HpBar::UpdatePosition(GameObject* relative_to)
{
	sf::Sprite* sprite = &relative_to->GetSprite();
	sf::Vector2f pos = sprite->getPosition();

	float offset =  -sprite->getGlobalBounds().height * 0.5f - GAME_CONST::HP_BAR_OFFSET;
	pos.y += offset;

	this->bar.setPosition(pos);
	this->bar_bg.setPosition(pos);
}

void HpBar::UpdateSize()
{
	this->bar.setSize(sf::Vector2f(this->hp / this->max_hp * GAME_CONST::HP_BAR_WIDTH, GAME_CONST::HP_BAR_HEIGHT)); //maybe bug with origin
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(this->bar_bg);
	window.draw(this->bar);
}

void HpBar::Update(GameObject* relative_to)
{
	this->UpdatePosition(relative_to);
	this->UpdateSize();
}