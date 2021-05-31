#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), "MyGameTitle"),
	delta_time_(0.0f),
	cursor_()
{	
	this->LoadTextures();
	this->SetupCamera();
	this->SetupPlayer();
	this->SetupCursor();

	//test game objects
	Enemy* new_e = Enemy::MakeRandomEnemy({ 550.0f, 0.0f }, &this->textures_);
	new_e->SetObjectToFollow(static_cast<Entity*>(this->game_objects_[0]));
	this->game_objects_.emplace_back(new_e);

	this->game_objects_.emplace_back(Enemy::MakeRandomEnemy({ 300.0f, 200.0f }, &this->textures_));

	this->game_objects_.emplace_back(new Gun({100.0f, 100.0f}, 10, &this->textures_));

	this->game_objects_.emplace_back(Terrain::MakeTerrain(TERRAIN::TREE, &this->textures_, { 200.0f, 300.0f }));
	this->game_objects_.emplace_back(Terrain::MakeTerrain(TERRAIN::WALL, &this->textures_, { -200.0f, -300.0f }));
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
	this->textures_.Add(TEXTURE::ENEMY_0, "assets/test_enemy_texture_0.png");
	this->textures_.Add(TEXTURE::ENEMY_1, "assets/test_enemy_texture_1.png");
	this->textures_.Add(TEXTURE::ENEMY_2, "assets/test_enemy_texture_2.png");
	this->textures_.Add(TEXTURE::HP_BAR, "assets/hp_bar.png");
	this->textures_.Add(TEXTURE::ITEM, "assets/item_1.png");
	this->textures_.Add(TEXTURE::SELECTED_ITEM, "assets/selected_item.png");
	this->textures_.Add(TEXTURE::ITEM_BG, "assets/items_bg.png");
	this->textures_.Add(TEXTURE::ITEM_GUN, "assets/item_gun.png");
	this->textures_.Add(TEXTURE::TREE, "assets/tree.png");
	this->textures_.Add(TEXTURE::WALL, "assets/wall.png");
	this->textures_.Add(TEXTURE::BULLET, "assets/bullet.png");
	this->textures_.Add(TEXTURE::CURSOR, "assets/cursor.png");
}

void Game::SetupCamera()
{
	this->camera_.Resize(this->window_);
}

void Game::SetupCursor()
{
	this->window_.setMouseCursorVisible(false);
	this->cursor_.Init(&this->textures_, TEXTURE::CURSOR);
}

void Game::UpdateCursor()
{
	this->cursor_.Update(this->window_, this->camera_);
}

void Game::SetupPlayer()
{
	Player* player = new Player({0.0f, 0.0f}, &this->textures_, TEXTURE::PLAYER);
	player->GetInventory()->Add(new Gun(sf::Vector2f{ 0.0f, 0.0f }, 100, &this->textures_, player, 0.5f));
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
	this->window_.clear(sf::Color(GAME_CONST::BG_R, GAME_CONST::BG_G, GAME_CONST::BG_B));
}

void Game::CheckObjectsCollision()
{
	for (auto it_a = this->game_objects_.begin(); it_a != this->game_objects_.end(); it_a++)
	{
		GameObject* obj_a = *it_a;
		Collider a_col = obj_a->GetCollider();
		float a_pbf = obj_a->GetPushBackForce();

		for (auto it_b = it_a + 1; it_b != this->game_objects_.end(); )
		{
			GameObject* obj_b = *it_b;
			Collider b_col = obj_b->GetCollider();
			float b_pbf = obj_b->GetPushBackForce();

			bool removed_b = false;

			// basic collision
			bool collision = a_pbf > b_pbf ? a_col.CheckCollision(b_col, a_pbf) : b_col.CheckCollision(a_col, b_pbf);

			// entity collisions

			if (GameObject::IsEntity(obj_a))
			{
				// entity - item
				if (collision && obj_b->GetType() == GAME_OBJECT_TYPE::ITEM)
				{
					Entity* entity = static_cast<Entity*>(obj_a);
					Item* item = static_cast<Item*>(obj_b);

					item->SetOwner(entity);
					entity->GetInventory()->Add(item);

					it_b = this->game_objects_.erase(it_b);
					removed_b = true;
				}
				else
				{
					// entity item collider - obj 2

					Entity* entity_a = static_cast<Entity*>(obj_a);
					Item* item = entity_a->GetInventory()->GetCurrentItem();
					if (item != nullptr)
					{
						bool item_collision = item->CheckCollision(obj_b);

						if (item_collision && GameObject::IsEntity(obj_b))
						{
							Entity* entity_b = static_cast<Entity*>(obj_b);
							bool died = !entity_b->LoseHp(item->GetPower());

							if (died)
							{
								it_b = this->game_objects_.erase(it_b);
								removed_b = true;
							}
						}
					}
				}
			}

			if (!removed_b)
			{
				++it_b;
			}

		}
	}


	for (unsigned int i=0; i<this->game_objects_.size(); i++)
	{
		GameObject* obj_a = this->game_objects_[i];
		Collider a_col = obj_a->GetCollider();
		float a_pbf = obj_a->GetPushBackForce();

		for (unsigned int j = i + 1; j < this->game_objects_.size(); j++) // +1 so it skips itself; i so it doesnt repeat checking collisions
		{
			GameObject* obj_b = this->game_objects_[j];
			Collider b_col = obj_b->GetCollider();
			float b_pbf = obj_b->GetPushBackForce();
			
			// basic collision
			bool collision = a_pbf > b_pbf ? a_col.CheckCollision(b_col, a_pbf) : b_col.CheckCollision(a_col, b_pbf);

			// entity - item collision

			if (collision && GameObject::IsEntity(obj_a) && obj_b->GetType() == GAME_OBJECT_TYPE::ITEM)
			{
				Entity* entity = static_cast<Entity*>(obj_a);
				Item* item = static_cast<Item*>(obj_b);
				
				item->SetOwner(entity);
				entity->GetInventory()->Add(item);

				auto it_it = this->game_objects_.begin() + j;
				it_it = this->game_objects_.erase(it_it);
			}

			// entity - item collision (when using item)
			
			if (GameObject::IsEntity(obj_a))
			{
				Entity* entity_a = static_cast<Entity*>(obj_a);
				Item* item = entity_a->GetInventory()->GetCurrentItem();
				if (item != nullptr)
				{
					bool item_collision = item->CheckCollision(obj_b);

					if (item_collision && GameObject::IsEntity(obj_b))
					{
						Entity* entity_b = static_cast<Entity*>(obj_b);
						bool died = !entity_b->LoseHp(item->GetPower());

						if (died)
						{
							auto ent_it = this->game_objects_.begin() + j;
							delete this->game_objects_[j];
							ent_it =  this->game_objects_.erase(ent_it);
						}
					}
				}
			}

			// TODO
			// obj_a item - obj_b
			// if true obj_b->LoseHp()
			// if LoseHp() returns false then erase object from game objects
		}
	}
}

void Game::UpdateGameObjects()
{		
	for (auto& game_obj : this->game_objects_)
	{
		game_obj->Update(this->delta_time_);
	}

	this->CheckObjectsCollision();
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
		Gun* gun = new Gun(sf::Vector2f(0.0f, 0.0f), 10, &this->textures_, player);
		player->GetInventory()->Add(gun);
	}
	//

	//test
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		player->LoseHp(0.01f);
	}
	//endtest

	//test enemy
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		Enemy* e = Enemy::MakeRandomEnemy({ float(rand() % 1000), float(rand() % 1000) }, &this->textures_);
		e->SetObjectToFollow(static_cast<Entity*>(this->game_objects_[0]));
		this->game_objects_.emplace_back(e);
	}
	//end test

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

void Game::DrawCursor()
{
	this->cursor_.Draw(this->window_);
}

void Game::Draw()
{
	this->ClearWindow();
	this->DrawGameObjects();
	this->DrawCursor();
	this->DisplayWindow();
}

void Game::Update()
{
	this->SetDeltaTime();
	this->HandleWindowEvents();
	this->HandleInputEvents();
	this->UpdateGameObjects();
	this->UpdateCamera();
	this->UpdateCursor();
}