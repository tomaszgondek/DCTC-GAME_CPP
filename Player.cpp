#include "Player.h"
#include <iostream>
using namespace std;

void Player::initTexture()
{
	this->playerTexture.loadFromFile("Graphics/kotdown.bmp");
	this->playerTextureUp.loadFromFile("Graphics/kotup.bmp");
}

void Player::initPlayer()
{
	this->movementSpeed = 2.f;
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setScale(sf::Vector2f(6.f, 6.f));
	this->playerSprite.setPosition(sf::Vector2f(150.f, 400));
	this->touchingDown = false;
	this->touchingUp = false;
}

Player::Player()
{
	this->initTexture();
	this->initPlayer();
}

Player::~Player()
{
}

void Player::changeTextureUp()
{
	this->playerSprite.setTexture(this->playerTextureUp);
}

void Player::changeTextureDown()
{
	this->playerSprite.setTexture(this->playerTexture);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}

void Player::update()
{

}

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
