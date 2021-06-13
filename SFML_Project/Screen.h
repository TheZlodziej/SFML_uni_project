#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameConstants.h"
#include "GameObject.h"

struct Label 
{
	sf::Text text;
	sf::Vector2f position;
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& origin);
};

enum class BUTTON_TYPE { CLOSE };

struct Button
{
	BUTTON_TYPE type;
	sf::RectangleShape rect;
	sf::Text text;
	sf::Vector2f position;
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& origin, const sf::Vector2f& mouse_pos);
	bool MouseOver(const sf::Vector2f& mouse_pos);
	void Hover(const sf::Vector2f& mouse_pos);
	bool Clicked(const sf::Vector2f mouse_pos);
};

enum class SCREEN_TYPE { START, PAUSE };

class Screen
{
private:
	GameObject* relative_to_;
	bool is_active_;
	sf::RectangleShape background_;
	std::vector<Label> labels_;
	std::vector<Button> buttons_;
	sf::Vector2f view_size_;
	sf::Vector2f origin_;

public:
	Screen(GameObject* relative_to = nullptr);
	virtual ~Screen();
	void Update(const sf::Vector2f& mouse_pos);
	void Draw(sf::RenderWindow& window);
	bool IsActive() const;
	void HandleButtonEvent(const BUTTON_TYPE& btn_type);
	void SetActive(const bool& state);
	void AddLabel(sf::Font* font, const std::string& string, const sf::Vector2f& position, const unsigned int& size = 32u);
	void AddButton(sf::Font* font, const BUTTON_TYPE& type, const std::string& string, const sf::Vector2f& position, const unsigned int& font_size = 32u);
};

