#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include <sstream>


class userTextInput
{
private:
	sf::Text textBox;
	sf::Text tt;
	sf::Text st;
	std::ostringstream text;
	bool is_selected;
	bool has_limit;
	int limit;
	int score;
	void inputLogic(int char_typed);
	void deleteLastChar();
	sf::Font font;
public:
	userTextInput(int size, sf::Color, bool sel, int score);
	~userTextInput();
	void setPosition(sf::Vector2f pos);
	void hasLimit(bool l);
	void setLimit(bool l, int lim);
	void setSelected(bool s);
	std::string getText();
	void render(sf::RenderTarget& target);
	void typed(sf::Event input);
};

