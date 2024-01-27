#include "userTextInput.h"
#include "SFML/Graphics.hpp"
#include "userTextInput.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

userTextInput::userTextInput(int size, sf::Color color, bool sel, int score)
{
	this->score = score;
	this->textBox.setCharacterSize(size);
	this->textBox.setFillColor(color);
	this->is_selected = sel;
	this->has_limit = false;
	this->limit = 10;
	this->font.loadFromFile("Fonts/FFFFORWA.ttf");
	this->textBox.setFont(font);
	this->tt.setCharacterSize(40);
	this->tt.setFont(font);
	this->tt.setFillColor(sf::Color::White);
	this->tt.setPosition(sf::Vector2f(300, 100));
	this->tt.setString("ENTER USERNAME:");
	this->st.setCharacterSize(30);
	this->st.setFont(font);
	this->st.setFillColor(sf::Color::White);
	this->st.setPosition(sf::Vector2f(300, 300));
	this->st.setString("SCORE: " + std::to_string(this->score));
	if (is_selected)
	{
		this->textBox.setString("_");
	}
	else
	{
		this->textBox.setString("");
	}
}

userTextInput::~userTextInput() {}

void userTextInput::setPosition(sf::Vector2f pos)
{
	this->textBox.setPosition(pos);
}

void userTextInput::hasLimit(bool l)
{
	this->has_limit = l;
}

void userTextInput::setLimit(bool l, int lim)
{
	this->has_limit = l;
	this->limit = lim;
}

void userTextInput::setSelected(bool s)
{
	this->is_selected = s;
	if (!this->is_selected)
	{
		std::string t = this->text.str();
		std::string new_t = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			new_t += t[i];
		}
		this->textBox.setString(new_t);

	}
}

std::string userTextInput::getText()
{
	return this->text.str();
}

void userTextInput::render(sf::RenderTarget& target)
{
	target.draw(this->textBox);
	target.draw(this->tt);
	target.draw(this->st);
}

void userTextInput::typed(sf::Event input)
{
	if (this->is_selected)
	{
		int char_typed_uni = input.text.unicode;
		if (char_typed_uni < 128)
		{
			if (this->has_limit)
			{
				if (this->text.str().length() <= this->limit)
				{
					this->inputLogic(char_typed_uni);
				}
				else if (this->text.str().length() > this->limit && char_typed_uni == DELETE_KEY)
				{
					this->deleteLastChar();
				}
				
			}
			else
			{
				this->inputLogic(char_typed_uni);
			}
		}
	}

}

void userTextInput::inputLogic(int char_typed)
{ 
	if (char_typed != DELETE_KEY && char_typed != ENTER_KEY && char_typed != ESCAPE_KEY)
	{
		this->text << static_cast<char>(char_typed);
	}
	else if (char_typed == DELETE_KEY)
	{
		if (this->text.str().length() > 0)
		{
			this->deleteLastChar();
		}
	}
	this->textBox.setString(this->text.str() + "_");
}

void userTextInput::deleteLastChar()
{
	std::string t = this->text.str();
	std::string new_t = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		new_t += t[i];
	}
	this->text.str("");
	this->text << new_t;
	this->textBox.setString(this->text.str());
}

