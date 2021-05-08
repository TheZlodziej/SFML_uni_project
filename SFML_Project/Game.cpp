#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), "MyGameTitle"),
	delta_time_(0.0f)
{	
	this->LoadTextures();
	this->SetupCamera();
	this->SetupPlayer();

	//test game objects
	sf::Sprite sprite(this->textures_.Get(TEXTURE::ENEMY_1));
	sprite.setScale(0.2f, 0.2f);

	sprite.setPosition(550,0);
	Entity* entity = new Entity(sprite);
	this->game_objects_.emplace_back(entity);

	sprite.setPosition(200, 200);
	Entity* entity1 = new Entity(sprite);
	this->game_objects_.emplace_back(entity1);
}

void Game::LoadTextures()
{
	this->textures_.Add(TEXTURE::PLAYER, "test_player_texture.png");
	this->textures_.Add(TEXTURE::ENEMY_1, "test.png");
}

Game::~Game() 
{
	for (auto game_obj : this->game_objects_)
	{
		delete game_obj;
	}
}

void Game::SetupCamera()
{
	this->camera_.Resize(this->window_);
	this->camera_.zoom(1.25f); //zoom has to come after resize
}

void Game::SetupPlayer()
{
	sf::Sprite player_sprite(this->textures_.Get(TEXTURE::PLAYER));
	player_sprite.setPosition(0, 0);
	Player* player = new Player(player_sprite);

	this->game_objects_.emplace_back(player);
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

		if (event.type == sf::Event::Resized)
		{
			this->camera_.Resize(this->window_);
		}
	}
}

void Game::ClearWindow()
{
	this->window_.clear(sf::Color(19,58,43));
}

void Game::UpdateGameObjects()
{	
	// tracking test with collision test // remove this later
	Entity* e1 = static_cast<Entity*>(game_objects_[0]);
	Entity* e = static_cast<Entity*>(game_objects_[1]);
	float distance = DistanceVec2f(e1->GetPosition(), e->GetPosition());
	if (distance <= 500.0f)
	{
		e->SetAcceleration(e->GetDirection(e1) * (3.0f / 5.0f * GAME_CONST::ENTITY_MOVE_ACCELERATION));
	}
	else
	{
		e->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
	}

	for (auto& game_obj : this->game_objects_)
	{
		game_obj->Update(this->delta_time_, this->game_objects_);
		//bool colliding = 
		//	std::any_of(this->game_objects_.begin(), this->game_objects_.end(),
		//		[game_obj](GameObject* obj) 
		//		{
		//			return game_obj != obj && game_obj->CollidingWith(obj);
		//		}
		//	);
		//
		//if (!colliding)
		//{
		//	// TODO: check for game object type and then do something based on its type
		//}
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
	this->delta_time_ = this->clock_.restart().asSeconds();
	//std::cout << this->delta_time_ << "\n";
}

void Game::KeyboardInput()
{
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	sf::Vector2f new_acceleration(0.0f,0.0f);
	float dir_force = GAME_CONST::ENTITY_MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		new_acceleration.x += -dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		new_acceleration.x += dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		new_acceleration.y += -dir_force;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		new_acceleration.y += dir_force;
	}

	player->SetAcceleration(new_acceleration);
}

void Game::MouseInput()
{
	// make player look at mouse
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	player->LookAtMouse(this->window_);
}

void Game::HandleInputEvents()
{
	this->KeyboardInput();
	this->MouseInput();
}

void Game::UpdateCamera()
{
	this->camera_.Update(this->game_objects_[0]->GetPosition()); //game_obj[0] reserved for player
	this->camera_.Attach(this->window_);
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
	this->UpdateCamera();
}