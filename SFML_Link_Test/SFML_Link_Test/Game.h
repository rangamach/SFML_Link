#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{

private:

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

	void InitializeVariables();
	void InitializeWindow();
	void InitializeEnemies();
	void InitializeFonts();
	void InitializeText();

	sf::RectangleShape enemy;
	sf::Vector2i mouse_positon_window;
	sf::Vector2f mouse_position_view;
	std::vector<sf::RectangleShape> enemies;

	sf::Font font;
	sf::Text ui_text;

	bool end_game;
	unsigned points;
	float enemy_spawn_timer;
	float enemy_spawn_timer_max;
	int max_enemies;
	bool mouse_pressed_down;
	int health;

public:
	Game();
	virtual ~Game();

	void SpawnEnemy();
	void PollEvents();
	void UpdateMousePositions();
	void UpdateEnemies();
	void Update();
	void RenderEnemies(sf::RenderTarget& target);
	void Render();
	void RenderText(sf::RenderTarget& target);
	void UpdateText();

	const bool GetWindowIsOpen() const;
	const bool GetEndGame() const;
};

