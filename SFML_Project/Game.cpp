#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), "MyGameTitle"),
	delta_time_(0.0f)
{	
	this->LoadTextures();
	this->SetupCamera();
	this->SetupPlayer();

	//test game objects
	Enemy* new_e = Enemy::MakeRandomEnemy({ 550.0f, 0.0f }, &this->textures_);
	new_e->SetObjectToFollow(static_cast<Entity*>(this->game_objects_[0]));
	this->game_objects_.emplace_back(new_e);

	this->game_objects_.emplace_back(Enemy::MakeRandomEnemy({ 300.0f, 200.0f }, &this->textures_));
}

Game::~Game()
{
	for (auto game_obj : this->game_objects_)
	{
		delete game_obj;
	}
}

void Game::LoadTextures()
{
	this->textures_.Add(TEXTURE::DEFAULT, "assets/test.png");
	this->textures_.Add(TEXTURE::PLAYER, "assets/test_player_texture.png");
	this->textures_.Add(TEXTURE::ENEMY_0, "assets/test_enemy_texture.png");
	this->textures_.Add(TEXTURE::ENEMY_1, "assets/test_enemy_texture.png");
	this->textures_.Add(TEXTURE::ENEMY_2, "assets/test_enemy_texture.png");
	this->textures_.Add(TEXTURE::HP_BAR, "assets/hp_bar.png");
	this->textures_.Add(TEXTURE::ITEM, "assets/item_1.png");
	this->textures_.Add(TEXTURE::SELECTED_ITEM, "assets/selected_item.png");
	this->textures_.Add(TEXTURE::ITEM_BG, "assets/items_bg.png");
	this->textures_.Add(TEXTURE::ITEM_GUN, "assets/item_gun.png");
}

void Game::SetupCamera()
{
	this->camera_.Resize(this->window_);
}

void Game::SetupPlayer()
{
	Player* player = new Player({0.0f, 0.0f}, &this->textures_, TEXTURE::PLAYER);
	player->GetInventory()->Add(new Gun(sf::Vector2f{ 0.0f, 0.0f }, 10, &this->textures_));
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
	for (auto& game_obj : this->game_objects_)
	{
		game_obj->Update(this->delta_time_);
	}

	for (unsigned int i = 1; i < this->game_objects_.size(); i++)
	{
		Collider playerCollider = this->game_objects_[0]->GetCollider();
		this->game_objects_[i]->GetCollider().CheckCollision(playerCollider, .5f);
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
	this->HandlePlayerMovement();
	this->HandlePlayerInventory();
}

void Game::HandlePlayerMovement()
{
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	sf::Vector2f new_acceleration(0.0f, 0.0f);
	float dir_force = GAME_CONST::ENTITY_MOVE_ACCELERATION;
	
	//gun test
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		Gun* gun = new Gun(sf::Vector2f(0.0f, 0.0f), 10, &this->textures_);
		player->GetInventory()->Add(gun);
	}
	//

	//test
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		player->LoseHp(0.01f);
	}
	//endtest

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

void Game::HandlePlayerInventory()
{
	Player* player = static_cast<Player*>(this->game_objects_[0]);
	Inventory* inv = player->GetInventory();

	for (int i = sf::Keyboard::Num0; i < sf::Keyboard::Num0 + 10; i++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			inv->SetCurrentItemIdx(i - sf::Keyboard::Num0 - 1);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->UseItem();
	}
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