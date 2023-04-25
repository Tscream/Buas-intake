#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"
#include <Windows.h>

namespace Tmpl8
{
	vec2 mousePos;
	vec2 cursor;
	clock_t playTime;

	void Game::MouseMove(int x, int y)
	{
		mousePos.x = mousePos.x + x;
		mousePos.y = mousePos.y + y;
		
		if (mousePos.x > 0 + cursor.x/2 && mousePos.x < ScreenWidth - cursor.x/2 && mousePos.y > 0 + cursor.y/2 && mousePos.y < ScreenHeight - cursor.y/2)
		{
			CursorVisual(mousePos.x, mousePos.y);
		}
	}

	void Game::CursorVisual(float x, float y)
	{
		float xPos1 = x - cursor.x / 2;
		float yPos1 = y - cursor.y / 2;
		float xPos2 = x + cursor.x / 2;
		float yPos2 = y + cursor.y / 2;

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0xffffff);
	}

	void Game::MouseDown(int button)
	{
		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
	}
	

	//void Game::Button(float posx, float posy, float width, float height)
	//{
	//	screen->Surface::Bar(posx - width/2, posy - height/2, posx + width/2, posy + height/2, 0xffffff);
	//}


	

	void Game::Init()
	{
		cursor.x = 20; //visual cursor width
		cursor.y = 20; //visual cursor height
		DWORD height = GetSystemMetrics(SM_CYSCREEN);
		std::cout << height << std::endl;

		Ball* playerBall = new Ball(100, 100, 10, 12, -10, 5, screen);

		playerBall->DrawLine();

		//CreateBall(ScreenWidth / 2, 350, 100);

	}
	void Game::Shutdown()
	{
		//save highscore
	}
	void Game::Tick(float deltaTime)
	{

		playTime = clock()/CLOCKS_PER_SEC;
		//Ball::t = playTime;

		//std::cout << playTime << std::endl;


		//screen->Clear(0x000000);
		//Button(ScreenWidth / 2, 250, 100, 30);
		//Button(ScreenWidth / 2, 300, 100, 30);

		/*Ball bal01;
		bal01.CreateBall(ScreenWidth / 2, 350, 100, screen);*/
		//MoveBall();

	}

	

	
	

};