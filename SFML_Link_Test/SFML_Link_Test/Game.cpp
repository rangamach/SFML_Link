#include "Game.h"

void Game::InitializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemy_spawn_timer_max = 10.f;
	this->enemy_spawn_timer = this->enemy_spawn_timer_max;
	this->max_enemies = 10;
	this->mouse_pressed_down = false;
	this->health = 10;
	this->end_game = false;

}

void Game::InitializeWindow()
{
	this->video_mode.height = 1080;
	this->video_mode.width = 1920;
	this->window = new sf::RenderWindow(this->video_mode, "Gamw1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::InitializeEnemies()
{
	this->enemy.setPosition(100.f,100.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
	this->enemy.setFillColor(sf::Color().Yellow);
}

void Game::InitializeFonts()
{
	if (this->font.loadFromFile("Fonts/Roboto"))
	{
		std::cout << "InitializeFonts-Successfully loaded font." << "\n";
	}
	else if (!this->font.loadFromFile("Fonts/Roboto"))
	{
		std::cout << "ERROR-InitializeFonts-Failed to load font." << "\n";
	}
}

void Game::InitializeText()
{
	this->ui_text.setFont(this->font);
	this->ui_text.setCharacterSize(12);
	this->ui_text.setFillColor(sf::Color().White);
	this->ui_text.setString("NONE");
}

Game::Game()
{
	this->InitializeVariables();
	this->InitializeWindow();
	this->InitializeFonts();
	this->InitializeText();
	this->InitializeEnemies();
}

Game::~Game()
{
	delete this->window;
}

void Game::SpawnEnemy()
{
	this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f );
	this->enemy.setFillColor(sf::Color().Green);
	this->enemies.push_back(this->enemy);
}

void Game::PollEvents()
{
	//Event Polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::UpdateMousePositions()
{
	this->mouse_positon_window = sf::Mouse::getPosition(*this->window);
	this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_positon_window);
}

void Game::UpdateEnemies()
{
	if (this->enemies.size() < this->max_enemies)
	{
		if (this->enemy_spawn_timer >= this->enemy_spawn_timer_max)
		{
			this->SpawnEnemy();
			this->enemy_spawn_timer = 0.f;
		}
		else
			this->enemy_spawn_timer += 1.f;
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouse_pressed_down == false)
		{
			this->mouse_pressed_down = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mouse_position_view))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 1;
					std::cout << "Points: " << this->points << "\n";
				}
			}
		}
	}
	else
	{
		this->mouse_pressed_down = false;
	}
}

void Game::Update()
{
	this->PollEvents();
	if (!this->end_game)
	{
		this->UpdateMousePositions();
		this->UpdateText();
		this->UpdateEnemies();
	}
	if (this->health <= 0)
		this->end_game = true;
}

void Game::RenderEnemies(sf::RenderTarget& target )
{
	for (auto& enemy : this->enemies)
		target.draw(enemy);
}

void Game::Render()
{
	this->window->clear();
	this->RenderEnemies(*this->window);
	this->RenderText(*this->window);
	this->window->display();
}

void Game::RenderText(sf::RenderTarget& target)
{
	target.draw(this->ui_text);  
}

void Game::UpdateText()
{
	std::stringstream string_stream;
	string_stream << "Points: " << this->points;
	this->ui_text.setString(string_stream.str());
}

const bool Game::GetWindowIsOpen() const
{
	return this->window->isOpen();
}

const bool Game::GetEndGame() const
{
	return this->end_game;
}
