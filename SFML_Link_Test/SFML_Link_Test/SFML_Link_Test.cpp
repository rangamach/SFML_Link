#include <iostream>
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;

	//Game Loop
	while (game.GetWindowIsOpen() && !game.GetEndGame())
	{

		//Update
		game.Update();

		//Render
		game.Render();

	}
	return 0;
}
