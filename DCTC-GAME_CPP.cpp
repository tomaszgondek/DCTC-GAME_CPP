#include "Game.h" 
#include <Windows.h> 
using namespace std;

int main(void)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
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