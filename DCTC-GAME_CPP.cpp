#include "Game.h" 
using namespace std;

int main(void)
{
	srand(static_cast<unsigned>(time(NULL)));
	//init game engine
	Game game;
	//game loop
	while (game.getWindowIsOpen())
	{
		game.update();
		game.render();
	}
}