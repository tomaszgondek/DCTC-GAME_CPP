#include "Game.h"
#include "Player.h"
#include "Menu.h"
#include <iostream>
#include <string.h>
#include "userTextInput.h"
#include <fstream>
using namespace std;

//Initialising all variables for later use
void Game::initVariables()
{
	this->window = nullptr;
	this->menu = nullptr;
	float obstacle_spawn_timer;
	float obstacle_spawn_timer_MAX;
	int score;
	int max_obstacles;
	float gapSize;
	float last_obstacle_y;
	float gravity;
	float speedup;
	float height;
	float width;
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
	this->width = 1200;
	this->height = 800;
	this->stage = 1;
	this->isRunning = 1;
}

//Initialising Window
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Don't Crash The Cat!", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Initialising obstacles
void Game::initObstacles()
{
	this->obstacle.setPosition(0, 0);
	this->obstacle.setSize(sf::Vector2f(100.f, 300.f));
	this->obstacle.setFillColor(sf::Color::White);
	this->obstacle_top.setPosition(0, 0);
	this->obstacle_top.setSize(sf::Vector2f(100.f, 300.f));
	this->obstacle_top.setFillColor(sf::Color::White);
}

//Initialising grpahics - setting textures and initial positions
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

sf::Font Game::getFont()
{
	return this->font;
}

//Constructor - calling all functions that initialise something
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initMenu();
	this->initOutline();
	this->initObstacles();
	this->initFont();
	this->initText();
	this->initPlayer();
	this->initBmp();
	this->initUItext();
	this->readSave();
}

//Deconstructor - deleting dynamic memory allocations to avoid memory leaks
Game::~Game()
{
	this->gameSave(this->userScores);
	delete this->window;
	delete this->player;
	delete this->menu;
}

//Getting window state - used to track if the main game loop should be still going
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

//Rendering background - drawing tiles on respective layers with updated/initial positions
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

//Updating background tiles to create parallax infinite-scrolling background effect
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

//Drawing welcome screen visible only on the first startup of the game
void Game::renderWelcome()
{
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->window->draw(this->welcomeScreen);
	this->window->draw(this->welcomeText);
	this->window->display();
}

//Drawing fail screen visible every time user looses
void Game::renderFail()
{
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->window->draw(this->failScreen);
	this->drawUItext();
	this->window->display();
}

//Initialising player as a new instance of the class
void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initMenu()
{
	this->menu = new Menu(this->width, this->height);
}

//Initialising font
void Game::initFont()
{
	this->font.loadFromFile("Fonts/FFFFORWA.ttf");
}

//Initialising text that is part of the game
void Game::initText()
{
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("NULL");
	this->scoreText.setPosition(sf::Vector2f(10, 760));
}

//Initiaslising text that is a part of UI
void Game::initUItext()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("Press 'C' to continue");
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

//Drawing UI text on screen
void Game::drawUItext()
{
	this->window->draw(this->uiText);
	this->window->draw(this->uiTextscore);
}

//Drawing text that diplay current user score
void Game::renderScoreText()
{
	this->window->draw(this->scoreText);
}

//Updating text that needs to be dynamically updated
void Game::updateText()
{
	stringstream ss;
	stringstream ss2;
	ss << "Score: " << this->score;
	this->scoreText.setString(ss.str());
	ss2 << this->score;
	this->uiTextscore.setString(ss2.str());
}

//Initialising outline of playing field
void Game::initOutline()
{
	this->outline.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x) - 10.f, 700.f));
	this->outline.setPosition(5, 5);
	this->outline.setFillColor(sf::Color(0, 0, 0, 0));
	this->outline.setOutlineColor(sf::Color::White);
	this->outline.setOutlineThickness(5.f);
}

//Drawing playing field
void Game::drawOutline()
{
	this->window->draw(this->outline);
}

//Spawning Obstacles - first we randomise bottom obstacle inside bounds, then draw upper obstacle above with given gap size in between
//then we push back the obstacles to obstacle vector to keeep track of them, and have a way of updating. Lastly we check if the 
//obstacles are on the screen. If not, we delete the obstacle
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

//Updating obstacles. We check how many obstacles there are, if less than maximum we allow the spawning of a new pair after a given time (which is bound to framerate - 60Hz).
//Then we iterate over obstacle vector to move them from left to right at a given speed. The speed is incresed with a score. Lastly, if we delete obstacle that means user 
//has succesfully cleared them, so we add +1 to score. To obtain that we need ignore every other point, as obstacles come in pairs.
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

//Rendering Obstacles - drawing them on screen, by iterating over each one and bliting them on screen
void Game::renderObstacles()
{
	for (auto& o : this->obstacles)
	{
		this->window->draw(o);
	}
}

void Game::menuLoop()
{
	while(this->isRunning)
	{
		this->menu->renderMenu(*this->window);
		while (this->window->pollEvent(this->m_ev))
		{
			if (this->m_ev.type == sf::Event::KeyPressed)
			{
				if (this->m_ev.key.code == sf::Keyboard::Up)
				{
					this->menu->moveUp();
				}
				if (this->m_ev.key.code == sf::Keyboard::Down)
				{
					this->menu->moveDown();
				}
				if (this->m_ev.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
					this->isRunning = false;
					break;
				}
				if (this->m_ev.key.code == sf::Keyboard::Enter)
				{
					if (this->menu->select_index == 0)
					{
						this->stage = 2;
						this->isRunning = false;
					}
					if (this->menu->select_index == 1)
					{
						this->stage = 4;
						this->isRunning = false;
					}
					if (this->menu->select_index == 2)
					{
						this->window->close();
						this->isRunning = false;
						break;
					}
				}
				cout << menu->select_index << endl;
			}
			if (this->m_ev.type == sf::Event::Closed)
			{
				this->window->close();
				this->isRunning = false;
				break;
			}

		}
		this->window->display();
	}
	this->isRunning = true;
}

void Game::stageManager()
{
	
	if (stage == 1) this->menuLoop();
	if (stage == 2) this->playLoop();
	if (stage == 3) this->endGameLoop();
	if (stage == 4) this->leaderboardLoop();
}

void Game::playLoop()
{
	while (this->isRunning)
	{
		//Calling essential functions as polling events, and updating game objects that need to be updated for the next frame
		this->pollEvents();
		this->updateBackground(this->offset);
		this->updateObstacles();
		this->updateText();
		this->player->update();
		//Calculating moving speed of things that move, that are not a player
		this->offset = -0.3 - (this->score * 0.01);
		//Handling keyboard input - checking if space is pressed or not
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			//Added gravity for incresed difficulty - the player accumulates acceleration when falling down, so the movement is smoother when he pulls up 
			this->gravity -= 0.12;
			//moving the player according to input and gravity
			this->player->move(0, -1.5 + this->gravity);
			//Changing texture of the cat according to movement
			this->player->changeTextureUp();
			//After user figures out that the space makes cat go up, no need to remind him of that
			this->tutorial_flag = false;
		}
		else
		{
			//If space not pressed cat go down, also there is positive acceleration if cat goes up
			this->gravity += 0.12;
			this->player->move(0, 1.5 + this->gravity);
			this->player->changeTextureDown();
		}

		//If cat touches floor or celling, it loses accumulated acceleration
		if (this->player->touchingUp || this->player->touchingDown)
		{
			this->gravity = 0.f;
		}

		//Handling collisions
		for (int i = 0; i < this->obstacles.size(); i++)
		{
			//If cat and obstacle intersects that means no bueno - game is lost
			if (this->player->boundingBox.intersects(this->obstacles[i].getGlobalBounds()))
			{
				this->end_game = true;
			}
		}
		//Failed screen - displays score and resets game
		if (this->end_game == true)
		{
			//Reseting speedup of parallax effects and obstacle speed
			this->speedup = -4.f;
			//Clearing obstacles
			this->obstacles.clear();
			//Resetting player position to initial values
			this->player->resetPos();
			//If user forgot that space makes cat go up during the next round, remind him again for good measures
			this->tutorial_flag = true;
			//Drawing only failed screen until told otherwise by pressing 'C' (which is also told to the user)
			this->stage = 3;
			this->isRunning = false;
			break;
		}
		this->render();
	}
	this->isRunning = true;
}

void Game::endGameLoop()
{
	while (this->isRunning)
	{
		this->renderFail();
		this->pollEvents();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		{
			this->end_game = false;
			break;
		}
	}
	this->isRunning = true;
	this->textBox = new userTextInput(30, sf::Color::White, 1, this->score);
	this->textBox->setPosition(sf::Vector2f(300, 200));
	this->textBox->setLimit(1, 20);
	while (this->isRunning)
	{
		this->window->clear(sf::Color::Black);
		while (this->window->pollEvent(this->t_ev))
		{
			switch (this->t_ev.type)
			{
				case sf::Event::TextEntered:
				{
					this->textBox->typed(this->t_ev);
				}
				case sf::Event::KeyPressed:
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
					{
						this->isRunning = false;
						this->stage = 1;
						break;
					}
				}
			}
		}
		this->textBox->render(*this->window);
		this->window->display();
	}
	this->isRunning = true;
	this->stage = 1;
	this->userScores.push_back(std::make_pair(this->textBox->getText(), this->score));
	this->gameSave(this->userScores);
	delete this->textBox;
	this->score = 0;
}

void Game::userInputLoop()
{
	
}

void Game::gameSave(std::vector<std::pair<std::string, int>> data)
{
	std::ofstream ofs;
	ofs.open("Saves/save.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofs.open("Saves/save.txt");
	for (auto const& x : data)
	{
		ofs << x.first << "." << x.second << endl;
	}
	ofs.close();
}

void Game::readSave()
{
	std::string temp, temp2, usr;
	bool b = false;
	int s;
	std::ifstream ifs;
	ifs.open("Saves/save.txt");
	while (std::getline(ifs, temp, '\n'))
	{
		std::stringstream ss3(temp);
		while (std::getline(ss3, temp2, '.'))
		{
			if (!b)
			{
				usr = temp2;
				b = true;
			}
			else
			{
				s = std::stoi(temp2);
				b = false;
			}
		}
		userScores.push_back(make_pair(usr, s));
	}
	ifs.close();
}

void Game::leaderboardLoop()
{
	std::sort(userScores.begin(), userScores.end(), [](auto& left, auto& right) 
		{
		return left.second > right.second;
		});
	sf::Text t, t2, t3;
	string tt;
	t.setFont(this->font);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(20);
	t2.setFont(this->font);
	t2.setFillColor(sf::Color::White);
	t2.setPosition(sf::Vector2f(600, 400));
	t2.setString("HALL OF FAME");
	t2.setCharacterSize(45);
	t3.setFont(this->font);
	t3.setFillColor(sf::Color::White);
	t3.setPosition(sf::Vector2f(600, 500));
	t3.setString("press 'c' to return");
	t3.setCharacterSize(25);
	while (this->isRunning)
	{
		this->window->clear(sf::Color::Black);
		for (int i = 0; i < userScores.size() - 1; i++)
		{
			t.setString(to_string(i + 1) + "." + userScores[i].first);
			t.setPosition(sf::Vector2f(100, 100 + 50 * i));
			this->window->draw(t);
			t.setString(to_string(userScores[i].second));
			t.setPosition(sf::Vector2f(430, 100 + 50 * i));
			this->window->draw(t);
		}
		while (this->window->pollEvent(this->t_ev))
		{
			switch (this->t_ev.type)
			{
			case sf::Event::KeyPressed:
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
				{
					this->isRunning = false;
					this->stage = 1;
					break;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					this->window->close();
					break;
				}
			}

			}
		}
		this->window->draw(t3);
		this->window->draw(t2);
		this->window->display();
	}
	this->isRunning = true;
}

//Polling events - we can handle events that happen inside. For this project the only necessary one is handling window closure.
//Essentially, if user closes it - it closes.
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

//Updating game - home to most of the game logic
void Game::update()
{
	this->stageManager();
}

//Rendering game objects that need to be rendered 
void Game::render()
{
	//Clearing screen of junk from previous frame
	this->window->clear(sf::Color(0, 0, 0, 255));
	//Rendering game objects
	this->renderBackground();
	this->renderObstacles();
	this->player->render(*this->window);
	this->drawOutline();
	this->renderScoreText();
	//If player has pressed space he probably realised how to control the cat, so it will not draw the tutorial text after
	if (this->tutorial_flag == true)
	{
		this->window->draw(this->tutorialText);
	}
	//Commiting changes to screen buffer
	this->window->display();
}




