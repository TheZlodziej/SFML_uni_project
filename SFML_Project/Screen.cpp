#include "Screen.h"

Screen::Screen(GameObject* relative_to):
    is_active_(false),
    view_size_(sf::Vector2f(0.0f, 0.0f)),
    relative_to_(relative_to),
    origin_(sf::Vector2f(0.0f, 0.0f))
{
    using namespace GAME_CONST;
    background_.setFillColor(SCREEN_BG_COLOR);
}

Screen::~Screen()
{
}

void Screen::Update(const sf::Vector2f& mouse_pos, sf::RenderWindow& window)
{
    // update view size
    this->view_size_ = window.getView().getSize();

    // update screen origin
    if (this->relative_to_ != nullptr)
    {
        this->origin_ = this->relative_to_->GetPosition();
    }

    // update bg
    this->background_.setSize(this->view_size_);
    sf::FloatRect bg_rect = this->background_.getGlobalBounds();
    sf::Vector2f bg_new_origin(bg_rect.width * 0.5f, bg_rect.height * 0.5f);
    this->background_.setOrigin(bg_new_origin);
    this->background_.setPosition(this->origin_);
   
    // update texts so they are relative to the origin
    for (auto& label : this->labels_)
    {
        label.Update(this->origin_);
    }

    // update buttons position
    for (auto& button : this->buttons_)
    {
        button.Update(this->origin_, mouse_pos);
        if (button.Clicked(mouse_pos))
        {
            this->HandleButtonEvent(button.type, window);
        }
    }
}

void Screen::Draw(sf::RenderWindow& window)
{
    window.draw(this->background_);
    for (auto& text_struct : this->labels_)
    {
        window.draw(text_struct.text);
    }

    for(auto& btn:this->buttons_)
    {
      btn.Draw(window);
    }
}

bool Screen::IsActive() const
{
    return this->is_active_;
}

void Screen::HandleButtonEvent(const BUTTON_TYPE& btn_type, sf::RenderWindow& window)
{
    switch (btn_type)
    {
    case BUTTON_TYPE::CLOSE:
        this->SetActive(false);
        break;
    
    case BUTTON_TYPE::CLOSE_WINDOW:
        window.close();
        break;
    }
    
}

void Screen::SetActive(const bool& state)
{
    this->is_active_ = state;
}

void Screen::AddLabel(sf::Font* font, const std::string& string, const sf::Vector2f& position, const unsigned int& size)
{
    sf::Text text;
    text.setFont(*font);
    text.setString(string);
    text.setCharacterSize(size);
    sf::FloatRect text_rect = text.getGlobalBounds();
    sf::Vector2f label_size(text_rect.width, text_rect.height);
    sf::Vector2f new_origin = label_size * 0.5f;
    text.setOrigin(new_origin);

    this->labels_.emplace_back(Label{text, position});
}

void Screen::AddButton(sf::Font* font, const BUTTON_TYPE& type, const std::string& string, const sf::Vector2f& position, const unsigned int& font_size)
{
    sf::Text text;
    text.setFont(*font);
    text.setCharacterSize(font_size);
    text.setString(string);
    sf::FloatRect text_rect = text.getGlobalBounds();
    sf::Vector2f text_size(text_rect.width, static_cast<float>(text.getCharacterSize()));
    text.setOrigin(text_size * 0.5f);

    sf::Vector2f margin_size(2.0f * GAME_CONST::BUTTON_LEFT_MARGIN, 2.0f * GAME_CONST::BUTTON_TOP_MARGIN);
    sf::RectangleShape rect(text_size + margin_size);
    sf::FloatRect rect_rect = rect.getGlobalBounds();
    sf::Vector2f rect_size(rect_rect.width, rect_rect.height);
    rect.setFillColor(GAME_CONST::BUTTON_COLOR);
    rect.setOrigin(rect_size * 0.5f);

    this->buttons_.emplace_back(Button{ type, rect, text, position });
}

void Button::Draw(sf::RenderWindow& window)
{
    window.draw(this->rect);
    window.draw(this->text);
}

void Button::Update(const sf::Vector2f& origin, const sf::Vector2f& mouse_pos)
{
    this->rect.setPosition(this->position + origin);
    this->text.setPosition(this->position + origin);
    this->Hover(mouse_pos);
}

bool Button::MouseOver(const sf::Vector2f& mouse_pos)
{
    sf::FloatRect btn_rect = this->rect.getGlobalBounds();
    bool left = mouse_pos.x >= btn_rect.left;
    bool right = mouse_pos.x <= btn_rect.left + btn_rect.width;
    bool top = mouse_pos.y >= btn_rect.top && mouse_pos.y;
    bool bottom = mouse_pos.y <= btn_rect.top + btn_rect.height;

    return left && right && top && bottom;
}

void Button::Hover(const sf::Vector2f& mouse_pos)
{
    if (this->MouseOver(mouse_pos))
    {
        this->rect.setFillColor(GAME_CONST::BUTTON_HOVER_COLOR);
    }
    else
    {
        this->rect.setFillColor(GAME_CONST::BUTTON_COLOR);
    }
}

bool Button::Clicked(const sf::Vector2f mouse_pos)
{
    return this->MouseOver(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Label::Draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}

void Label::Update(const sf::Vector2f& origin)
{
    this->text.setPosition(this->position + origin);
}
