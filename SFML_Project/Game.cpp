#include "Game.h"

Game::Game() : 
	window_(sf::VideoMode(800, 600), "MyGameTitle")
{
	// test drawing
	sf::Texture texture;
	texture.loadFromFile("test.png");

	sf::Sprite sprite(texture);
	sprite.setPosition(0,0);
	sprite.setScale(.5, .5);
	// window_.draw(sprite);
	
	GameObject* entity = new Entity(sprite, sf::Vector2f(100,100), sf::Vector2f(-10, -10));
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
		game_obj->Update(this->DeltaTime());
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

float Game::DeltaTime()
{
	return this->clock_.restart().asSeconds();
}

void Game::Draw()
{
	this->ClearWindow();
	this->DrawGameObjects();
	this->DisplayWindow();	
}

void Game::Update()
{
	this->HandleWindowEvents();
	this->UpdateGameObjects();
}