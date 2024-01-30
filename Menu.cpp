#include "Game.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "Menu.h"

Menu::Menu(float width, float height)
{
	this->width = width;
	this->height = height;
	this->font.loadFromFile("Fonts/FFFFORWA.ttf");
	this->play1 = " PLAY";
	this->play2 = ">PLAY";
	this->leaderboard1 = " LEADERBOARD";
	this->leaderboard2 = ">LEADERBOARD";
	this->quit1 = " QUIT";
	this->quit2 = ">QUIT";
	this->select_index = 0;

	this->title.setFillColor(sf::Color::White);
	this->title.setFont(this->font);
	this->title.setCharacterSize(50);
	this->title.setString("DON'T CRASH THE CAT!");
	this->title.setPosition(sf::Vector2f(this->width / 2 - 400, 100));

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->play1);
	this->text.setPosition(sf::Vector2f(this->width / 2, 300));
	this->texts.push_back(text);

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->leaderboard1);
	this->text.setPosition(sf::Vector2f(this->width / 2, 400));
	this->texts.push_back(text);

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->quit1);
	this->text.setPosition(sf::Vector2f(this->width / 2, 500));
	this->texts.push_back(text);

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->play2);
	this->text.setPosition(sf::Vector2f(this->width / 2, 300));
	this->texts.push_back(text);

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->leaderboard2);
	this->text.setPosition(sf::Vector2f(this->width / 2, 400));
	this->texts.push_back(text);

	this->text.setFillColor(sf::Color::White);
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setString(this->quit2);
	this->text.setPosition(sf::Vector2f(this->width / 2, 500));
	this->texts.push_back(text);
}

Menu::~Menu()
{
}

void Menu::moveUp()
{
	this->select_index--;
	if (this->select_index < 0)
	{
		this->select_index = 0;
	}
}

void Menu::moveDown()
{
	this->select_index++;
	if (this->select_index > 2)
	{
		this->select_index = 2;
	}
}

void Menu::renderMenu(sf::RenderTarget& target)
{
	target.clear(sf::Color::Black);
	target.draw(this->title);
	if (this->select_index == 0)
	{
		target.draw(this->texts[3]);
		target.draw(this->texts[1]);
		target.draw(this->texts[2]);
	}
	else if (this->select_index == 1)
	{
		target.draw(this->texts[0]);
		target.draw(this->texts[4]);
		target.draw(this->texts[2]);
	}
	else if (this->select_index == 2)
	{
		target.draw(this->texts[0]);
		target.draw(this->texts[1]);
		target.draw(this->texts[5]);
	}
}


