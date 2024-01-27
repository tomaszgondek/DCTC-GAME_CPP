#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include <sstream>
#include "Player.h"
#include "userTextInput.h"
#include "Menu.h"
/*
* Main game class - game engine
* For details check Game.cpp
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
	float speedup;
	float offset;
	float width;
	float height;
	bool end_game;
	bool ignore_next_point;
	int high_score;
	bool welcome_flag;
	bool tutorial_flag;
	bool isRunning;
	unsigned int stage;
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
	sf::Sprite starsT1;
	sf::Sprite starsT2;
	sf::Sprite starsT3;
	sf::Sprite starsT11;
	sf::Sprite starsT21;
	sf::Sprite starsT31;
	sf::Sprite staticStars;
	sf::Sprite staticStars2;
	sf::Texture starTexture;
	sf::Texture starTexture2;
	sf::Texture starTexture3;
	std::vector<std::pair<std::string, int>> userScores;
	Player* player;
	Menu* menu;
	userTextInput* textBox;
	//Resources
	sf::Font font;
	//Text
	sf::Text scoreText;
	sf::Text uiTextscore;
	sf::Text uiText;
	sf::Text welcomeText;
	sf::Text tutorialText;
	//Events
	sf::Event ev;
	sf::Event m_ev;
	sf::Event t_ev;
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
	void renderBackground();
	void updateBackground(float offset);
	void renderWelcome();
	void renderFail();
	void initPlayer();
	void initMenu();
	void initFont();
	void initText();
	void initUItext();
	void drawUItext();
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
	void menuLoop();
	void stageManager();
	void playLoop();
	void endGameLoop();
	void userInputLoop();
	void gameSave(std::vector<std::pair<std::string, int>> data);
	void readSave();
	void leaderboardLoop();
	sf::Font getFont();
};

