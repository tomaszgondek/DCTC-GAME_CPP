#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include <sstream>
#include "Player.h"
/*
* Main game class - game engine
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	//Game logic
	float obstacle_spawn_timer;
	float obstacle_spawn_timer_MAX;
	float gapSize;
	int score;
	int max_obstacles;
	float last_obstacle_y;
	float obstacle_tracker;
	float gravity;
	bool end_game;
	//Game objects
	std::vector<sf::RectangleShape> obstacles;
	std::vector<sf::RectangleShape> obstacles_top;
	sf::RectangleShape obstacle;
	sf::RectangleShape obstacle_top;
	sf::RectangleShape outline;
	sf::Sprite failScreen;
	sf::Sprite welcomeScreen;
	sf::Texture welcomeBmp;
	sf::Texture failBmp;
	Player* player;
	//Resources
	sf::Font font;
	//Text
	sf::Text scoreText;
	//Events
	sf::Event ev;
	//private functions
	void initVariables();
	void initWindow();
	void initObstacles();
	void initBmp();

public:
	//Constructor / deconstructor
	Game();
	virtual ~Game();
	//Accessors
	const bool getWindowIsOpen() const;
	//functions
	void renderWelcome();
	void renderFail();
	void initPlayer();
	void initFont();
	void initText();
	void renderScoreText();
	void updateText();
	void initOutline();
	void drawOutline();
	void spawnObstacle();
	void updateObstacles();
	void renderObstacles();
	void pollEvents();
	void update();
	void render();
	
};

