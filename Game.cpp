#include "Game.h"
using namespace std;

void Game::initVariables()
{
	this->window = nullptr;
	//Game logic
	float obstacle_spawn_timer;
	float obstacle_spawn_timer_MAX;
	int score;
	int max_obstacles;
	float gapSize;
	float last_obstacle_y;
	this->gapSize = 250.f;
	this->obstacle_spawn_timer_MAX = 180.f;
	this->obstacle_spawn_timer = this->obstacle_spawn_timer_MAX;
	this->score = 0;
	this->max_obstacles = 16;
}

//Initializing Window
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Don't Crash The Cat!", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Initializing obstacles
void Game::initObstacles()
{
	this->obstacle.setPosition(0, 0);
	this->obstacle.setSize(sf::Vector2f(100.f, 300.f));
	this->obstacle.setFillColor(sf::Color::White);
	this->obstacle_top.setPosition(0, 0);
	this->obstacle_top.setSize(sf::Vector2f(100.f, 300.f));
	this->obstacle_top.setFillColor(sf::Color::White);
}

//Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initOutline();
	this->initObstacles();
	this->initFont();
	this->initText();
}

//Deconstructor
Game::~Game()
{
	delete this->window;
}

//Getting window state
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::initFont()
{
	this->font.loadFromFile("Fonts/FFFFORWA.ttf");
}

void Game::initText()
{
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("NULL");
	this->scoreText.setPosition(sf::Vector2f(10, 760));
}

void Game::renderScoreText()
{
	this->window->draw(this->scoreText);
}

void Game::updateText()
{
	stringstream ss;
	ss << "Score: " << this->score;
	this->scoreText.setString(ss.str());
}

void Game::initOutline()
{
	this->outline.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x) - 10.f, 700.f));
	this->outline.setPosition(5, 5);
	this->outline.setFillColor(sf::Color(0, 0, 0, 0));
	this->outline.setOutlineColor(sf::Color::White);
	this->outline.setOutlineThickness(5.f);
}

void Game::drawOutline()
{
	this->window->draw(this->outline);
}

//Spawning Obstacles
void Game::spawnObstacle()
{
	//bottom
	this->last_obstacle_y = static_cast<float>(rand() % (static_cast<int>(this->window->getSize().y - this->gapSize + 50)));
	if (this->last_obstacle_y < this->gapSize)
		this->last_obstacle_y = this->gapSize + 50;
	this->obstacle.setPosition
	(
		1200.f,
		last_obstacle_y
	);
	this->obstacle.setSize(sf::Vector2f
	(
		100.f, 
		this->window->getSize().y - 90 - this->obstacle.getPosition().y
	)
	);
	this->obstacle.setFillColor(sf::Color::White);
	this->obstacles.push_back(this->obstacle);
	//top
	this->obstacle_top.setPosition
	(
		1200.f,
		0
	);
	this->obstacle_top.setSize(sf::Vector2f
	(
		100.f,
		this->last_obstacle_y - this->gapSize
	)
	);
	this->obstacle_top.setFillColor(sf::Color::White);
	this->obstacles.push_back(this->obstacle_top);
}
//Updating obstacles
void Game::updateObstacles()
{
	if (this->obstacles.size() < this->max_obstacles)
	{
		if (this->obstacle_spawn_timer >= this->obstacle_spawn_timer_MAX)
		{
			this->spawnObstacle();
			this->obstacle_spawn_timer = 0.f;
		}
		else
		{
			this->obstacle_spawn_timer += 1.f;
		}
	}
	//Move obstacles
	for (int i = 0; i < this->obstacles.size(); i++)
	{
		this->obstacles[i].move(-4.f, 0.f);
		//check if outside of the screen
		if (this->obstacles[i].getPosition().x + this->obstacles[i].getSize().x <= 0)
		{
			this->obstacles.erase(this->obstacles.begin() + i);
			this->score += 1;
		}

	}
}

//Rendering Obstacles
void Game::renderObstacles()
{
	for (auto& o : this->obstacles)
	{
		this->window->draw(o);
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
		}
	}
}

//Updating game
void Game::update()
{
	this->pollEvents();
	this->updateObstacles();
	this->updateText();
}

//Rendering things
void Game::render()
{
	//rendering game objects
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderObstacles();
	this->drawOutline();
	this->renderScoreText();
	this->window->display();
}


