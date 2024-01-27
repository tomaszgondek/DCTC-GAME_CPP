#include "Game.h" 
#include <Windows.h> 
#include <stdlib.h>  

using namespace std;

int main(void)
{
	//Hiding console
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
	//Initialising pseudorandom number generation with some junk data seed
	srand(static_cast<unsigned>(time(NULL)));
	//Init game engine
	Game game;
	//Main game loop - stops when user closes window
	while (game.getWindowIsOpen())
	{
		game.update();
	}
	//CloseWindow(hWnd);
	return 0;
}