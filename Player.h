#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

//Player class, handles player - input, graphics etc.
class Player
{
private:
	//Variables
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::Texture playerTextureUp;
	float movementSpeed;
	
	//Functions
	void initTexture();
	void initPlayer();
public:
	bool touchingUp;
	bool touchingDown;
	//Constructor / Decunstructor
	Player();
	virtual ~Player();
	//Functions
	void changeTextureUp();
	void changeTextureDown();
	void render(sf::RenderTarget& target);
	void update();
	void move(const float dirX, const float dirY);
};

