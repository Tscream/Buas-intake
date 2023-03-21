#include "game.h"
#include "surface.h"
#include "iostream"

using namespace std;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		cout<<"Init"<<endl;
		cout << screen -> GetWidth() << endl;

	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	void Game::DrawI(const float speed_x, const float speed_y, const float i_width, const float i_height, const int color)
	{
		screen->Line(10 + speed_x, 10 + speed_y, 10 + i_width + speed_x, 10 + speed_y, color);
		screen->Line(10 + i_width / 2 + speed_x, 10 + speed_y, 10 + i_width / 2 + speed_x, 10 + i_height + speed_y, color);
		screen->Line(10 + speed_x, 10 + i_height + speed_y, 10 + i_width + speed_x, 10 + i_height + speed_y, color);
	}

	void Game::DrawCentredI(float speed_x, float speed_y, float i_width, float i_height, int color)
	{
		const float start_x = screen->GetWidth() / 2 - i_width / 2;
		const float start_y = screen->GetHeight() / 2 - i_height / 2;

		screen->Line(start_x + speed_x, start_y + speed_y, start_x + i_width + speed_x, start_y + speed_y, color);
		screen->Line(start_x + i_width / 2 + speed_x, start_y + speed_y, start_x + i_width / 2 + speed_x, start_y + i_height + speed_y, color);
		screen->Line(start_x + speed_x, start_y + i_height + speed_y, start_x + i_width + speed_x, start_y + i_height + speed_y, color);
	}



	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		DrawI(0, 0, 100, 200, 0x0000ff);
		DrawCentredI(0, 0, 100, 200, 0xffffff);
	}
};