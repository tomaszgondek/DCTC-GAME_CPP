#include "Player.h"
#include <iostream>
using namespace std;

//Initialising player textures
void Player::initTexture()
{
	this->playerTexture.loadFromFile("Graphics/kotdown.bmp");
	this->playerTextureUp.loadFromFile("Graphics/kotup.bmp");
}

//Initilising player - position, scale and variables
void Player::initPlayer()
{
	this->movementSpeed = 2.f;
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setScale(sf::Vector2f(6.f, 6.f));
	this->playerSprite.setPosition(sf::Vector2f(150.f, 400));
	this->touchingDown = false;
	this->touchingUp = false;
}

//Initilising things that need to be initialised, and getting bounding box for collision detection
Player::Player()
{
	this->boundingBox = this->playerSprite.getGlobalBounds();
	this->initTexture();
	this->initPlayer();
}

//Destructor - no dynamic allocations, so no deletions
Player::~Player()
{
}

//Method to obain bounding box from player sprite
void Player::getBoundingBox()
{
	this->boundingBox = this->playerSprite.getGlobalBounds();
}

//Method that allows changing textures, while keeping them private
void Player::changeTextureUp()
{
	this->playerSprite.setTexture(this->playerTextureUp);
}

void Player::changeTextureDown()
{
	this->playerSprite.setTexture(this->playerTexture);
}

//Resetting player position to initial values
void Player::resetPos()
{
	this->playerSprite.setPosition(sf::Vector2f(150.f, 400.f));
}

//Rendering player on the given surface
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}

//Updating - only thing we need to update is bounding box, as other updates are handled outside
void Player::update()
{
	this->getBoundingBox();
}

//Moving player according to input from game, and throwing flags that check if cat touch celling or floor
void Player::move(const float dirX, const float dirY)
{
	if (this->playerSprite.getPosition().y < 6)
	{
		this->touchingUp = true;
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, 6.f);
	}	
	else if (this->playerSprite.getPosition().y >= 642)
	{
		this->touchingDown = true;
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, 642.f);
	}
	else
	{
		this->touchingDown = false;
		this->touchingUp = false;
	}
	this->playerSprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
