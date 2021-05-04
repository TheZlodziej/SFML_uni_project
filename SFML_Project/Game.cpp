#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), "MyGameTitle"),
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
	this->enemy_texture_.loadFromFile("test.png");

	sf::Sprite sprite(this->enemy_texture_);
	sprite.setPosition(0,0);
	sprite.setScale(.25, .25);
	// window_.draw(sprite);
	
	Entity* entity = new Entity(sprite);
	//entity->SetAcceleration(sf::Vector2f(200.0f, 0.0f));
	this->game_objects_.emplace_back(entity);

	//Entity* entity1 = new Entity(sprite);
	//entity1->SetAcceleration(sf::Vector2f(0.0f, 200.0f));
	//this->game_objects_.emplace_back(entity1);
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

	// tracking test // remove this later
	Entity* e1 = static_cast<Entity*>(game_objects_[0]);
	Entity* e = static_cast<Entity*>(game_objects_[1]);
	e->SetAcceleration(e->GetDirection(e1) * (3.0f/5.0f * this->delta_time_ * GAME_CONST::ENTITY_MOVE_ACCELERATION));
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
	this->delta_time_ = this->clock_.restart().asSeconds();
	std::cout << this->delta_time_ << "\n";
}

void Game::KeyboardInput()
{
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	sf::Vector2f new_acceleration(0.0f,0.0f);
	float dir_force = GAME_CONST::ENTITY_MOVE_ACCELERATION * this->delta_time_;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		new_acceleration.x += -dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		new_acceleration.x += dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		new_acceleration.y += -dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		new_acceleration.y += dir_force;
	}

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