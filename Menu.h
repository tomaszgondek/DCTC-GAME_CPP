#pragma once
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#define MAX_ITEMS 3
#include <string>
#include <stdio.h>
#include "GameObject.h"

class Menu : public GameObject
{
private: 
	float width, height;
	sf::Font font;
	sf::Text text;
	sf::Text title;
public:
	Menu(float width, float height);
	~Menu();
	int select_index;
	std::string play1, play2, leaderboard1, leaderboard2, quit1, quit2;
	std::vector<sf::Text> texts;
	std::vector<sf::Text> d_texts;
	void moveUp();
	void moveDown();
	void render(sf::RenderTarget& target);
};
