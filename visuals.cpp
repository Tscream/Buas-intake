#include "game.h"
#include "surface.h"
#include "visuals.h"
#include "template.h"
#include "iostream"
//#include <Windows.h>


namespace Tmpl8
{
	Game game;

	void Visuals::CursorVisual(int x, int y)
	{
		vec2 cursor;
		cursor.x = 20;
		cursor.y = 20;

		/*int xPos1 = x - cursor.x / 2;
		int yPos1 = y - cursor.y / 2;
		int xPos2 = x + cursor.x / 2;
		int yPos2 = y + cursor.y / 2;

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0xffffff);*/

		game.screen->Bar(10, 10, 100, 100, 0xffffff);

		std::cout << "Feest" << std::endl;

	}

	void Visuals::Button(int posx, int posy, int width, int height)
	{
		game.screen->Surface::Bar(posx - width / 2, posy - height / 2, posx + width / 2, posy + height / 2, 0xffffff);
	}

};