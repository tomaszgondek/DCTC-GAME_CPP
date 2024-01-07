#include "Game.h"
#include "Player.h"
#include <iostream>
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
	float gravity;
	float speedup;
	float offset;
	bool end_game;
	bool ignore_next_point;
	int high_score;
	bool welcome_flag;
	bool tutorial_flag;
	this->gapSize = 250.f;
	this->obstacle_spawn_timer_MAX = 180.f;
	this->obstacle_spawn_timer = this->obstacle_spawn_timer_MAX;
	this->score = 0;
	this->max_obstacles = 16;
	this->gravity = 0.f;
	this->speedup = -4.f;
	this->end_game = false;
	this->ignore_next_point = false;
	this->offset = 0;
	this->high_score = 0;
	this->welcome_flag = true;
	this->tutorial_flag = true;
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

void Game::initBmp()
{
	this->welcomeBmp.loadFromFile("Graphics/welcome.bmp");
	this->welcomeScreen.setTexture(this->welcomeBmp);
	this->failBmp.loadFromFile("Graphics/failed.bmp");
	this->failScreen.setTexture(this->failBmp);
	this->welcomeScreen.setScale(9.375, 9.375);
	this->failScreen.setScale(9.375, 9.375);
	this->welcomeScreen.setPosition(0.f, 100.f);
	this->failScreen.setPosition(0.f, 100.f);
	this->starTexture.loadFromFile("Graphics/starsv3.png");
	this->starTexture2.loadFromFile("Graphics/starsB.png");
	this->starsT1.setTexture(this->starTexture);
	this->starsT1.setPosition(0, 30);
	this->starsT2.setTexture(this->starTexture);
	this->starsT2.setPosition(650.f, 30);
	this->starsT3.setTexture(this->starTexture);
	this->starsT3.setPosition(1300, 30);
	this->starsT11.setTexture(this->starTexture2);
	this->starsT11.setPosition(0, 30);
	this->starsT21.setTexture(this->starTexture2);
	this->starsT21.setPosition(650.f, 30);
	this->starsT31.setTexture(this->starTexture2);
	this->starsT31.setPosition(1300, 30);
	this->starTexture3.loadFromFile("Graphics/staticstars.png");
	this->staticStars.setTexture(this->starTexture3);
	this->staticStars2.setTexture(this->starTexture3);
	this->staticStars2.setPosition(1000, 0);
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
	this->initPlayer();
	this->initBmp();
	this->initUItext();
}

//Deconstructor
Game::~Game()
{
	delete this->window;
	delete this->player;
}

//Getting window state
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::renderBackground()
{
	this->window->draw(this->starsT1);
	this->window->draw(this->starsT2);
	this->window->draw(this->starsT3);
	this->window->draw(this->starsT11);
	this->window->draw(this->starsT21);
	this->window->draw(this->starsT31);
	this->window->draw(this->staticStars);
	this->window->draw(this->staticStars2);
}

void Game::updateBackground(float offset)
{
	this->starsT1.move(offset, 0);
	this->starsT2.move(offset, 0);
	this->starsT3.move(offset, 0);
	if (this->starsT1.getPosition().x <= -650)
	{
		this->starsT1.setPosition(this->starsT3.getPosition().x + 650, 30);
	}
	if (this->starsT2.getPosition().x <= -650)
	{
		this->starsT2.setPosition(this->starsT1.getPosition().x + 650, 30);
	}
	if (this->starsT3.getPosition().x <= -650)
	{
		this->starsT3.setPosition(this->starsT2.getPosition().x + 650, 30);
	}
	this->starsT11.move(offset/8, 0);
	this->starsT21.move(offset/8, 0);
	this->starsT31.move(offset/8, 0);
	if (this->starsT11.getPosition().x <= -650)
	{
		this->starsT11.setPosition(this->starsT31.getPosition().x + 650, 30);
	}
	if (this->starsT21.getPosition().x <= -650)
	{
		this->starsT21.setPosition(this->starsT11.getPosition().x + 650, 30);
	}
	if (this->starsT31.getPosition().x <= -650)
	{
		this->starsT31.setPosition(this->starsT21.getPosition().x + 650, 30);
	}
}

void Game::renderWelcome()
{
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->window->draw(this->welcomeScreen);
	this->window->draw(this->welcomeText);
	this->window->display();
}

void Game::renderFail()
{
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->window->draw(this->failScreen);
	this->drawUItext();
	this->window->display();
}

void Game::initPlayer()
{
	this->player = new Player();
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

void Game::initUItext()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("Press 'C' to restart");
	this->uiText.setPosition(425.f, 740.f);
	this->uiTextscore.setFont(this->font);
	this->uiTextscore.setCharacterSize(80);
	this->uiTextscore.setFillColor(sf::Color::White);
	this->uiTextscore.setString("NULL");
	this->uiTextscore.setPosition(900.f, 450.f);
	this->welcomeText.setFont(this->font);
	this->welcomeText.setCharacterSize(30);
	this->welcomeText.setFillColor(sf::Color::White);
	this->welcomeText.setString("Press 'C' to start");
	this->welcomeText.setPosition(430.f, 740.f);
	this->tutorialText.setFont(this->font);
	this->tutorialText.setCharacterSize(30);
	this->tutorialText.setFillColor(sf::Color::White);
	this->tutorialText.setString("Press SPACE to move up");
	this->tutorialText.setPosition(400.f, 760.f);
}

void Game::drawUItext()
{
	this->window->draw(this->uiText);
	this->window->draw(this->uiTextscore);
}

void Game::renderScoreText()
{
	this->window->draw(this->scoreText);
}

void Game::updateText()
{
	stringstream ss;
	stringstream ss2;
	ss << "Score: " << this->score;
	this->scoreText.setString(ss.str());
	ss2 << this->score;
	this->uiTextscore.setString(ss2.str());
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
	this->last_obstacle_y = this->gapSize - 100 + static_cast<float>(rand() % (static_cast<int>(this->window->getSize().y - this->gapSize)));
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
		if (this->obstacle_spawn_timer >= this->obstacle_spawn_timer_MAX || this->obstacles.size() == 0)
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
		this->obstacles[i].move(this->speedup, 0.f);
		//check if outside of the screen
		if (this->obstacles[i].getPosition().x + this->obstacles[i].getSize().x <= 0)
		{
			this->obstacles.erase(this->obstacles.begin() + i);
			if (this->ignore_next_point == false)
			{
				this->score += 1;
				this->speedup -= 0.2;
				this->ignore_next_point = true;
			}				
			else this->ignore_next_point = false;
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
	//welcome screen at startup
	if (this->welcome_flag == true)
	{
		while (this->welcome_flag == true)
		{
			this->renderWelcome();
			this->pollEvents();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				this->welcome_flag = false;
				break;
			}
		}
	}
	this->pollEvents();
	this->updateBackground(this->offset);
	this->updateObstacles();
	this->updateText();
	this->player->update();
	this->offset = -0.3 - (this->score * 0.01);
	//Handling keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->gravity -= 0.12;
		this->player->move(0, -1.5 + this->gravity);
		this->player->changeTextureUp();
		this->tutorial_flag = false;
	}
	else
	{
		this->gravity += 0.12;
		this->player->move(0, 1.5 + this->gravity);
		this->player->changeTextureDown();
	}
	if (this->player->touchingUp || this->player->touchingDown)
	{
		this->gravity = 0.f;
	}
	//Handling collisions
	for (int i = 0; i < this->obstacles.size(); i++)
	{
		if (this->player->boundingBox.intersects(this->obstacles[i].getGlobalBounds()))
		{
			this->end_game = true;
		}
	}
	//Failed screen
	if (this->end_game == true)
	{
		this->speedup = -4.f;
		this->score = 0;
		this->obstacles.clear();
		this->player->resetPos();
		this->tutorial_flag = true;
		while (this->end_game == true)
		{
			this->renderFail();
			this->pollEvents();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				this->end_game = false;
				break;
			}
		}
	}
}

//Rendering things
void Game::render()
{
	//rendering game objects
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderBackground();
	this->renderObstacles();
	this->player->render(*this->window);
	this->drawOutline();
	this->renderScoreText();
	if (this->tutorial_flag == true)
	{
		this->window->draw(this->tutorialText);
	}
	this->window->display();
}


