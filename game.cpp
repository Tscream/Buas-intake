#include "game.h"
#include "surface.h"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite tank(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	static Sprite ball(new Surface("assets/ball.png"), 1);


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		for (int c = 0; c < 36; c++) //c is the amount of tanks per row (colums)
		{
			for (int r = 0; r < 12; r++) //r is the amount of rows
			{
				tank.SetFrame(c);
				tank.Draw(screen, c * 40, r * 40);
			}
		}

		ball.DrawScaled(30, 30, 150, 150, screen);
	}
};