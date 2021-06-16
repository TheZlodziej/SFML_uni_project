#include "Game.h"

Game::Game() :
	window_(sf::VideoMode(GAME_CONST::WINDOW_WIDTH, GAME_CONST::WINDOW_HEIGHT), GAME_CONST::GAME_TITLE),
	delta_time_(0.0f),
	player_(nullptr),
	font_(nullptr),
	paused_(false),
	enemies_spawn_timer_(0.0f),
	items_spawn_timer_(0.0f)
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
	this->textures_.Add(TEXTURE::HAND, "assets/hand.png");
}

void Game::SetupCamera()
{
	this->camera_.Resize(this->window_);
}

void Game::SpawnEnemies()
{
	this->enemies_spawn_timer_ += this->delta_time_;

	if (this->enemies_spawn_timer_ < GAME_CONST::ENEMY_SPAWN_TIME)
	{
		return;
	}

	this->enemies_spawn_timer_ = 0.0f;

	sf::Vector2f enemy_pos = GetRandomVec2fInRange(GAME_CONST::ENEMY_SPAWN_RANGE, this->player_->GetPosition());
	Enemy* enemy = Enemy::MakeRandomEnemy(enemy_pos, &this->textures_);
	enemy->SetObjectToFollow(this->player_);
	
	this->enemies_.emplace_back(enemy);
}

bool Game::AnyScreenActive()
{
	return std::any_of(this->screens_.begin(), this->screens_.end(),
		[](const std::pair<SCREEN_TYPE, Screen>& screen)
		{
			return screen.second.IsActive();
		}
	);
}

void Game::PauseIfScreenOpened()
{
	if (this->AnyScreenActive())
	{
		this->paused_ = true;
	}
}

void Game::SetupCursor()
{
	this->window_.setMouseCursorVisible(false);
	this->cursor_.Init(&this->textures_, TEXTURE::CURSOR);
}

void Game::SetupScreens()
{
	Screen start_screen(this->player_);
	start_screen.AddLabel(this->font_, GAME_CONST::GAME_TITLE, { 0.0f, -200.0f }, 52u);
	start_screen.AddLabel(this->font_, "Controls:", { 0.0f, -110.0f }, 32u);
	start_screen.AddLabel(this->font_, "movement: AWSD", { 0.0f, -70.0f }, 28u);
	start_screen.AddLabel(this->font_, "fire: Space", { 0.0f, -40.0f }, 28u);
	start_screen.AddLabel(this->font_, "switch inventory item: 1~9", { 0.0f, -10.0f }, 28u);
	start_screen.AddLabel(this->font_, "remove item from inventory: Q", { 0.0f, 20.0f }, 28u);
	start_screen.AddLabel(this->font_, "pause: P", { 0.0f, 50.0f }, 28u);
	start_screen.AddLabel(this->font_, "Press the button below to play!", { 0.0f, 100.0f }, 22u);
	start_screen.AddButton(this->font_, BUTTON_TYPE::CLOSE, "    PLAY    ", { 0.0f, 200.0f });
	start_screen.SetActive(true);
	this->screens_.insert(std::make_pair(SCREEN_TYPE::START, start_screen));

	Screen pause_screen(this->player_);
	pause_screen.AddLabel(this->font_, "GAME PAUSED", { 0.0f, -100.0f }, 32u);
	pause_screen.AddLabel(this->font_, "The Game will be paused until you press the button below...", { 0.0f, -25.0f }, 24u);
	pause_screen.AddButton(this->font_, BUTTON_TYPE::CLOSE, "Resume The Game", { 0.0f, 100.0f }, 32u);
	this->screens_.insert(std::make_pair(SCREEN_TYPE::PAUSE, pause_screen));

	Screen end_screen(this->player_);
	end_screen.AddLabel(this->font_, "YOU DIED!", { 0.0f, -100.0f });
	end_screen.AddButton(this->font_, BUTTON_TYPE::CLOSE_WINDOW, "Exit The Game", { 0.0f, 100.0f }, 32u);
	this->screens_.insert(std::make_pair(SCREEN_TYPE::END, end_screen));
}

void Game::Pause()
{
	if (!this->AnyScreenActive())
	{
		this->screens_.at(SCREEN_TYPE::PAUSE).SetActive(!this->screens_.at(SCREEN_TYPE::PAUSE).IsActive());
	}
}

void Game::SpawnItems()
{
	this->items_spawn_timer_ += this->delta_time_;

	if (this->items_spawn_timer_ >= GAME_CONST::ITEM_SPAWN_TIME)
	{
		this->items_spawn_timer_ = 0.0f;

		int rand_nb = std::rand() % 2;
		unsigned int rand_dur = 10 + std::rand() % 41;
		float rand_cd = 0.1f + static_cast<float>(std::rand() % 21) / 10.0f;
		sf::Vector2f item_pos = GetRandomVec2fInRange(GAME_CONST::ITEM_SPAWN_RANGE, this->player_->GetPosition());

		Item* new_item = nullptr;

		switch (rand_nb)
		{
		case 0:
			new_item = new Gun(item_pos, rand_dur, &this->textures_, nullptr, rand_cd);
			break;

		case 1:
			new_item = new Sword(item_pos, rand_dur, &this->textures_, nullptr, rand_cd);
			break;
		}

		this->items_.emplace_back(new_item);
	}
}

void Game::ScreenInput()
{
	static bool p_released = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (p_released)
		{
			p_released = false;
			this->Pause();
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

		if (event.type == sf::Event::LostFocus)
		{
			this->Pause();
		}
	}
}

void Game::ClearWindow()
{
	this->window_.clear(GAME_CONST::BG_COLOR);
}

void Game::RemoveOutOfMapObjects()
{
	auto out_of_map = [](GameObject* obj)
	{
		sf::Vector2f o_pos = obj->GetPosition();
		sf::Vector2f map_size(static_cast<float>(GAME_CONST::MAP_WIDTH), static_cast<float>(GAME_CONST::MAP_HEIGHT));

		return o_pos.x < -map_size.x * 0.5f || o_pos.x > map_size.x * 0.5f || o_pos.y < -map_size.y * 0.5f || o_pos.y > map_size.y * 0.5f;
	};

	for (auto it = this->enemies_.begin(); it != this->enemies_.end(); )
	{
		if (out_of_map(*it))
		{
			delete* it;
			it = this->enemies_.erase(it);
			this->enemies_spawn_timer_ = GAME_CONST::ENEMY_SPAWN_TIME;
		}
		else
		{
			++it;
		}
	}

	for (auto it = this->items_.begin(); it != this->items_.end(); )
	{
		if (out_of_map(*it))
		{
			delete* it;
			it = this->items_.erase(it);
			this->items_spawn_timer_ = GAME_CONST::ITEM_SPAWN_TIME;
		}
		else
		{
			++it;
		}
	}

	for (auto it = this->terrain_.begin(); it != this->terrain_.end(); )
	{
		if (out_of_map(*it))
		{
			delete* it;
			it = this->terrain_.erase(it);
		}
		else
		{
			++it;
		}
	}
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
		bool collision = false;

		if (pl_pbf > e_pbf)
		{
			collision = pl_coll.CheckCollision(e_coll, pl_pbf);
		}
		else
		{
			collision = e_coll.CheckCollision(pl_coll, e_pbf);
		}

		if (collision)
		{
			e->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
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
			bool collision = false;

			if (e1_pbf > e2_pbf)
			{
				collision = e1_coll.CheckCollision(e2_coll, e1_pbf);
			}
			else
			{
				collision = e2_coll.CheckCollision(e1_coll, e2_pbf);
			}

			if (collision)
			{
				e1->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
				e2->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
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
				this->screens_[SCREEN_TYPE::END].SetActive(true);
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

	this->SpawnItems();
	this->SpawnEnemies();

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
	this->RemoveOutOfMapObjects();
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
	
	static bool q_released = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (q_released)
		{
			q_released = false;
			inv->Remove(inv->GetCurrentItemIndex());
		}
	}
	else
	{
		q_released = true;
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
	if (!this->screens_[SCREEN_TYPE::PAUSE].IsActive())
	{
		this->paused_ = false;
	}

	for (auto& [key, screen] : this->screens_)
	{
		if (screen.IsActive())
		{
			screen.Update(this->cursor_.GetPosition(), this->window_);
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
	this->PauseIfScreenOpened();
}