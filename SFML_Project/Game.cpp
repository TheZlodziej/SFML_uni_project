#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(800, 600), "MyGameTitle"),
	delta_time_(0.0f)
{
	// test player
	this->player_texture_.loadFromFile("test_player_texture.png");
	sf::Sprite player_sprite(this->player_texture_);
	player_sprite.setPosition(0, 0);
	Player* player = new Player(player_sprite);
	this->game_objects_.emplace_back(player);
	// test drawing
	sf::Texture texture;
	texture.loadFromFile("test.png");

	sf::Sprite sprite(texture);
	sprite.setPosition(0,0);
	sprite.setScale(.5, .5);
	// window_.draw(sprite);
	
	GameObject* entity = new Entity(sprite, sf::Vector2f(100.0f,100.0f), sf::Vector2f(-1.0f, -1.0f));
	this->game_objects_.emplace_back(entity);
	// texture is destroyed after leaving the constructor
	// so you need to save the texture on the object or
	// in private variable
}

Game::~Game() 
{
	for (auto game_obj : this->game_objects_)
	{
		delete game_obj;
	}
}

bool Game::IsRunning()
{
	return this->window_.isOpen();
}

void Game::HandleWindowEvents()
{
	sf::Event event;
	while (this->window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window_.close();
		}
	}
}

void Game::ClearWindow()
{
	this->window_.clear(sf::Color(19,58,43));
}

void Game::UpdateGameObjects()
{
	for (auto& game_obj : this->game_objects_)
	{
		game_obj->Update(this->delta_time_);
	}
}

void Game::DrawGameObjects()
{
	for (auto& game_obj : this->game_objects_)
	{
		game_obj->Draw(this->window_);
	}
}

void Game::DisplayWindow()
{
	this->window_.display();
}

void Game::SetDeltaTime()
{
	//std::cout << this->clock_.restart().asSeconds() << "\n";
	this->delta_time_ = this->clock_.restart().asSeconds();
}

void Game::KeyboardInput()
{
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	sf::Vector2f new_acceleration = player->GetAcceleration();
	float dir_val = 1000.0f * this->delta_time_;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		new_acceleration.x += -dir_val;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		new_acceleration.x += dir_val;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		new_acceleration.y += -dir_val;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		new_acceleration.y += dir_val;
	}

	ClampVector2f(new_acceleration, -30.0f, 30.0f); //clamp to max speed
	//std::cout << new_acceleration.x << " " << new_acceleration.y <<"\n";
	player->SetAcceleration(new_acceleration);
}

void Game::HandleInputEvents()
{
	this->KeyboardInput();
}

void Game::Draw()
{
	this->ClearWindow();
	this->DrawGameObjects();
	this->DisplayWindow();	
}

void Game::Update()
{
	this->SetDeltaTime();
	this->HandleWindowEvents();
	this->HandleInputEvents();
	this->UpdateGameObjects();
}