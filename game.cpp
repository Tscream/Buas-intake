#include "game.h"
#include "surface.h"
#include "visuals.h"
#include "template.h"
#include "iostream"
//#include <Windows.h>


namespace Tmpl8
{
	vec2 mousePos;
	vec2 cursor;
	Visuals visuals;

	void Game::MouseMove(int x, int y)
	{
		mousePos.x = mousePos.x + x;
		mousePos.y = mousePos.y + y;
		
		if (mousePos.x > 0 + cursor.x/2 && mousePos.x < ScreenWidth - cursor.x/2 && mousePos.y > 0 + cursor.y/2 && mousePos.y < ScreenHeight - cursor.y/2)
		{
			visuals.CursorVisual(mousePos.x, mousePos.y);
		}


	}

	void Game::MouseDown(int button)
	{
		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;

		/*pseudo code
		if(menu == true)
		{
			if(collision with button 1)
			{
				change coler of button 1;
			}
			if(collision with button 2)
			{
				change coler of button 2;
			}
			else return;
		}

		if(game == true)
		{
			bullet vx = mousex;
			bullet vy = mousey;
		}
		

		*/

	}
	

	void Game::Init()
	{
		cursor.x = 20; //visual cursor width
		cursor.y = 20; //visual cursor height
		//DWORD height = GetSystemMetrics(SM_CYSCREEN);
		//std::cout << height << std::endl;
	}
	void Game::Shutdown()
	{
		//save highscore
	}
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0x000000);
		/*Button(ScreenWidth / 2, 250, 100, 30);
		Button(ScreenWidth / 2, 300, 100, 30);*/



		/*pseudo code
		if(menu == true)
		{
			Button(ScreenWidth / 2, 250, 100, 30);
			Button(ScreenWidth / 2, 300, 100, 30);
		}
		if(game == true)
		{
			
		}


		*/

	}

	

	
	

};