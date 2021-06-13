#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), "MyGameTitle"),
	delta_time_(0.0f),
	player_(nullptr),
	font_(nullptr),
	paused_(false)
{	
	this->LoadTextures();
	this->LoadFont();
	this->SetupCamera();
	this->SetupPlayer();
	this->SetupEnemies();
	this->SetupTerrain();
	this->SetupItems();
	this->SetupCursor();
	this->SetupScreens();
}

Game::~Game()
{
	delete this->font_;
	delete this->player_;

	for (auto& i : this->items_)
	{
		delete i;
	}

	for (auto& e : this->enemies_)
	{
		delete e;
	}

	for (auto& t : this->terrain_)
	{
		delete t;
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
	this->textures_.Add(TEXTURE::WALL, "assets/wall.png", true);
	this->textures_.Add(TEXTURE::BULLET, "assets/bullet.png");
	this->textures_.Add(TEXTURE::CURSOR, "assets/cursor.png");
	this->textures_.Add(TEXTURE::BOX, "assets/box.png");
	this->textures_.Add(TEXTURE::SWORD, "assets/sword.png");
}

void Game::SetupCamera()
{
	this->camera_.Resize(this->window_);
}

void Game::CheckIfGamePaused()
{
	paused_ = std::any_of(this->screens_.begin(), this->screens_.end(), 
		[](const std::pair<SCREEN_TYPE, Screen>& screen) 
		{
			return screen.second.IsActive();
		}
	);
}

void Game::SetupCursor()
{
	this->window_.setMouseCursorVisible(false);
	this->cursor_.Init(&this->textures_, TEXTURE::CURSOR);
}

void Game::SetupScreens()
{
	Screen start_screen(this->player_);
	start_screen.AddLabel(this->font_, "TESTOWY EKRAN", { 0.0f, -100.0f }, 32u);
	start_screen.AddButton(this->font_, BUTTON_TYPE::CLOSE, "TESTOWY PRZYCISK", { 0.0f, 200.0f });
	start_screen.SetActive(true);
	this->screens_.insert(std::make_pair(SCREEN_TYPE::START, start_screen));

	Screen pause_screen(this->player_);
	pause_screen.AddLabel(this->font_, "GAME PAUSED", { 0.0f, -100.0f }, 32u);
	pause_screen.AddLabel(this->font_, "Press P to resume...", { 0.0f, -50.0f }, 24u);
	pause_screen.AddButton(this->font_, BUTTON_TYPE::CLOSE, "Resume The Game", { 0.0f, 100.0f }, 32u);
	this->screens_.insert(std::make_pair(SCREEN_TYPE::PAUSE, pause_screen));
}

void Game::ScreenInput()
{
	static bool p_released = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (p_released)
		{
			p_released = false;
			this->screens_.at(SCREEN_TYPE::PAUSE).SetActive(!this->screens_.at(SCREEN_TYPE::PAUSE).IsActive());
		}
	}
	else
	{
		p_released = true;
	}
}

void Game::UpdateCursor()
{
	this->cursor_.Update(this->window_, this->camera_);
}

void Game::SetupPlayer()
{
	Player* player = new Player({ 0.0f, 0.0f }, &this->textures_, TEXTURE::PLAYER);
	player->GetInventory()->Add(new Gun(sf::Vector2f{ 0.0f, 0.0f }, 100, &this->textures_, player, 0.5f), this->font_);
	player->GetInventory()->Add(new Sword(sf::Vector2f{ 0.0f, 0.0f }, 30, &this->textures_, player), this->font_);
	this->player_ = player;
}

void Game::SetupTerrain()
{
	// boxes
	Terrain* b1 = Terrain::MakeTerrain(TERRAIN::BOX, &this->textures_, { 600.0f, 600.0f });
	this->terrain_.emplace_back(b1);

	// trees
	Terrain* t1 = Terrain::MakeTerrain(TERRAIN::TREE, &this->textures_, { 200.0f, 300.0f });
	this->terrain_.emplace_back(t1);

	// bounding walls
	float map_w = GAME_CONST::MAP_WIDTH;
	float map_h = GAME_CONST::MAP_HEIGHT;

	Terrain* w1 = Terrain::MakeTerrain(TERRAIN::WALL, &this->textures_, { -map_w *0.5f, 0.0f }, { 1.0f, map_h/100.0f });
	this->terrain_.emplace_back(w1);

	Terrain* w2 = Terrain::MakeTerrain(TERRAIN::WALL, &this->textures_, { map_w * 0.5f, 0.0f }, { 1.0f, map_h/100.0f });
	this->terrain_.emplace_back(w2);

	Terrain* w3 = Terrain::MakeTerrain(TERRAIN::WALL, &this->textures_, { 0.0f, -map_h *0.5f }, { map_w/100.0f + 1.0f, 1.0f });
	this->terrain_.emplace_back(w3);

	Terrain* w4 = Terrain::MakeTerrain(TERRAIN::WALL, &this->textures_, { 0.0f, map_h * 0.5f }, { map_w/100.0f + 1.0f, 1.0f });
	this->terrain_.emplace_back(w4);
}

void Game::SetupEnemies()
{
	Enemy* e1 = Enemy::MakeRandomEnemy({ 550.0f, 0.0f }, &this->textures_);
	e1->SetObjectToFollow(this->player_);
	this->enemies_.emplace_back(e1);

	Enemy* e2 = Enemy::MakeRandomEnemy({ 300.0f, 200.0f }, &this->textures_);
	e2->SetObjectToFollow(this->player_);
	this->enemies_.emplace_back(e2);
	
}

void Game::SetupItems()
{
	Gun* gun = new Gun({ 100.0f, 100.0f }, 10, &this->textures_);
	this->items_.push_back(gun);

	Gun* gun1 = new Gun({ -500.0f, 100.0f }, 100, &this->textures_, nullptr, 0.1f, 1000.0f, 100.0f);
	this->items_.push_back(gun1);

	Sword* sword = new Sword({ 300.0f, -100.0f }, 100, &this->textures_, nullptr);
	this->items_.push_back(sword);
}

bool Game::IsRunning()
{
	return this->window_.isOpen();
}

void Game::LoadFont()
{
	sf::Font* font = new sf::Font();

	if (!font->loadFromFile("assets/test_font.ttf"))
	{
		throw std::invalid_argument("Couldn't open font file.");
	}
	
	this->font_ = font;
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
	this->window_.clear(GAME_CONST::BG_COLOR);
}

void Game::CheckObjectsCollision()
{
	// player - enemy
	// enemy - enemy
	// enemy - terrain
	// player - terrain
	// enemy - item
	// player - item
	// player_item - enemy
	// plyer_item - terrain
	// enemy_item - terrain
	// enemy_item - player

	// player - enemy
	Collider pl_coll = this->player_->GetCollider();
	float pl_pbf = this->player_->GetPushBackForce();

	for (auto& e : this->enemies_)
	{
		Collider e_coll = e->GetCollider();
		float e_pbf = e->GetPushBackForce();

		if (pl_pbf > e_pbf)
		{
			pl_coll.CheckCollision(e_coll, pl_pbf);
		}
		else
		{
			e_coll.CheckCollision(pl_coll, e_pbf);
		}
	}

	// enemy - enemy
	for (auto& e1 : this->enemies_)
	{
		Collider e1_coll = e1->GetCollider();
		float e1_pbf = e1->GetPushBackForce();

		for (auto& e2 : this->enemies_)
		{
			if (e1 == e2)
			{
				continue;
			}

			Collider e2_coll = e2->GetCollider();
			float e2_pbf = e2->GetPushBackForce();

			if (e1_pbf > e2_pbf)
			{
				e1_coll.CheckCollision(e2_coll, e1_pbf);
			}
			else
			{
				e2_coll.CheckCollision(e1_coll, e2_pbf);
			}
		}
	}

	// enemy - terrain
	for (auto& e : this->enemies_)
	{
		Collider e_coll = e->GetCollider();
		float e_pbf = e->GetPushBackForce();
		
		for (auto& t : this->terrain_)
		{
			Collider t_coll = t->GetCollider();
			float t_pbf = t->GetPushBackForce();

			if (e_pbf > t_pbf)
			{
				e_coll.CheckCollision(t_coll, e_pbf);
			}
			else
			{
				t_coll.CheckCollision(e_coll, t_pbf);
			}
		}
	}

	// player - terrain
	for (auto& t : this->terrain_)
	{
		Collider t_coll = t->GetCollider();
		float t_pbf = t->GetPushBackForce();

		if (pl_pbf > t_pbf)
		{
			pl_coll.CheckCollision(t_coll, pl_pbf);
		}
		else
		{
			t_coll.CheckCollision(pl_coll, t_pbf);
		}
	}

	// player - item
	for (auto it = this->items_.begin(); it != this->items_.end();)
	{
		Collider i_coll = (*it)->GetCollider();
		
		bool collision = pl_coll.CheckCollision(i_coll, 1.0f);
		if (collision)
		{
			// don't free memory here because the inventory takes care of it 
			// and you don't want to remove it anyway
			// because you want to keep the item

			(*it)->SetOwner(this->player_);
			this->player_->GetInventory()->Add(*it, this->font_);
			it = this->items_.erase(it);
		}
		else
		{
			++it;
		}
	}

	// enemy - item
	for (auto it = this->items_.begin(); it != this->items_.end();)
	{
		Collider i_coll = (*it)->GetCollider();
		bool collision = false;

		for (auto& e : this->enemies_)
		{
			Collider e_coll = e->GetCollider();
			collision = e_coll.CheckCollision(i_coll, 1.0f);

			if (collision)
			{
				(*it)->SetOwner(e);
				e->GetInventory()->Add(*it);
				e->GetInventory()->SelectBestItem();
				it = this->items_.erase(it);
				break;
			}
		}
		
		if (!collision)
		{
			++it;
		}
	}

	// player_item - enemy
	Item* pl_it = this->player_->GetInventory()->GetCurrentItem();
	if (pl_it != nullptr)
	{
		for (auto e_it = this->enemies_.begin(); e_it != this->enemies_.end();)
		{
			bool collision = pl_it->CheckCollision(*e_it);
			bool died = false;
			
			if (collision)
			{
				died = !((*e_it)->LoseHp(pl_it->GetPower()));
			}

			if (died)
			{
				delete (*e_it);
				e_it = this->enemies_.erase(e_it);
			}
			else
			{
				++e_it;
			}
		}
	}

	// player_item - terrain
	if (pl_it != nullptr)
	{
		for (auto& t : this->terrain_)
		{
			pl_it->CheckCollision(t);
		}
	}

	// enemy_item - terrain
	for (auto& e : this->enemies_)
	{
		Item* it = e->GetInventory()->GetCurrentItem();
		if (it == nullptr)
		{
			continue;
		}

		for (auto& t : this->terrain_)
		{
			it->CheckCollision(t);
		}
	}

	// enemy_item - player
	for (auto& e : this->enemies_)
	{
		Item* it = e->GetInventory()->GetCurrentItem();

		if (it == nullptr)
		{
			continue;
		}
		
		bool collision = it->CheckCollision(this->player_);

		if (collision)
		{
			bool died = !(this->player_->LoseHp(it->GetPower()));

			if (died)
			{
				// game over !
				this->window_.close();
			}
		}
	}
}

void Game::UpdateGameObjects()
{		
	if (this->paused_) 
	{
		return;
	}

	for (auto& game_obj : this->terrain_)
	{
		game_obj->Update(this->delta_time_);
	}

	for (auto& game_obj : this->items_)
	{
		game_obj->Update(this->delta_time_);
	}

	for (auto& game_obj : this->enemies_)
	{
		game_obj->Update(this->delta_time_);
	}

	this->player_->Update(this->delta_time_);

	this->CheckObjectsCollision();
}

void Game::DrawGameObjects()
{
	for (auto& game_obj : this->terrain_)
	{
		game_obj->Draw(this->window_);
	}

	for (auto& game_obj : this->items_)
	{
		game_obj->Draw(this->window_);
	}

	for (auto& game_obj : this->enemies_)
	{
		game_obj->Draw(this->window_);
	}

	this->player_->Draw(this->window_);
}

void Game::DisplayWindow()
{
	this->window_.display();
}

void Game::SetDeltaTime()
{
	this->delta_time_ = this->clock_.restart().asSeconds();
}

void Game::KeyboardInput()
{
	this->HandlePlayerMovement();
	this->HandlePlayerInventory();
}

void Game::HandlePlayerMovement()
{
	sf::Vector2f new_acceleration(0.0f, 0.0f);
	float dir_force = GAME_CONST::ENTITY_MOVE_ACCELERATION;

	//gun test
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		Gun* gun = new Gun(sf::Vector2f(0.0f, 0.0f), 10, &this->textures_, this->player_);
		this->player_->GetInventory()->Add(gun);
	}
	//

	//test
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		this->player_->LoseHp(0.01f);
	}
	//endtest

	//test enemy
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		Enemy* e = Enemy::MakeRandomEnemy({ float(rand() % 1000), float(rand() % 1000) }, &this->textures_);
		e->SetObjectToFollow(this->player_);
		this->enemies_.emplace_back(e);
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

	this->player_->SetAcceleration(new_acceleration);
}

void Game::HandlePlayerInventory()
{
	Inventory* inv = this->player_->GetInventory();

	for (int i = sf::Keyboard::Num0; i < sf::Keyboard::Num0 + 10; i++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			inv->SetCurrentItemIdx(i - sf::Keyboard::Num0 - 1);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->player_->UseItem();
	}
}

void Game::MouseInput()
{
	// make player look at mouse
	this->player_->LookAtMouse(this->window_);
}

void Game::HandleInputEvents()
{
	this->ScreenInput();
	if (this->paused_)
	{
		return;
	}
	this->KeyboardInput();
	this->MouseInput();
}

void Game::UpdateCamera()
{
	this->camera_.Update(this->player_->GetPosition());
	this->camera_.Attach(this->window_);
}

void Game::DrawCursor()
{
	this->cursor_.Draw(this->window_);
}

void Game::DrawScreens()
{
	for (auto& [key, screen] : this->screens_)
	{
		if (screen.IsActive())
		{
			screen.Draw(this->window_);
		}
	}
}

void Game::UpdateScreens()
{
	for (auto& [key, screen] : this->screens_)
	{
		if (screen.IsActive())
		{
			screen.Update(this->cursor_.GetPosition());
		}
	}
}

void Game::Draw()
{
	this->ClearWindow();
	this->DrawGameObjects();
	this->DrawScreens();
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
	this->UpdateScreens();
	this->CheckIfGamePaused();
}