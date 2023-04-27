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
	float playTime;

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


	Ball* ball01{ nullptr };
	Ball* ball02{ nullptr };
	Ball* ball03{ nullptr };
	Ball* ball04{ nullptr };
	Ball* ball05{ nullptr };
	Ball* ball06{ nullptr };



	void Game::Init()
	{
		cursor.x = 20; //visual cursor width
		cursor.y = 20; //visual cursor height
		DWORD height = GetSystemMetrics(SM_CYSCREEN);
		std::cout << height << std::endl;

		ball01 = new Ball(ScreenWidth / 2, 100, 75, 12, -10, screen, &playTime);
		//ball02 = new Ball(ScreenWidth / 2, 200, 100, 10, -12, screen, playTime);
		//ball03 = new Ball(ScreenWidth / 2, 300, 125, 12, -14, screen, playTime);
		//ball04 = new Ball(ScreenWidth / 2, 400, 150, 14, -10, screen, playTime);
		//ball05 = new Ball(ScreenWidth / 2, 500, 175, 14, -14, screen, playTime);
		//ball06 = new Ball(ScreenWidth / 2, 600, 200, 10, -10, screen, playTime);

	}
	void Game::Shutdown()
	{
		//save highscore
	}
	void Game::Tick(float deltaTime)
	{
		//Button(ScreenWidth / 2, 250, 100, 30);
		//Button(ScreenWidth / 2, 300, 100, 30);


		playTime = playTime + deltaTime;


		screen->Clear(0x000000);
		ball01->DisplayBall();
		//ball02->DisplayBall();		
		//ball03->DisplayBall();
		//ball04->DisplayBall();
		//ball05->DisplayBall();
		//ball06->DisplayBall();

		ball01->MoveBall();
		//ball02->MoveBall();
		//ball03->MoveBall();
		//ball04->MoveBall();
		//ball05->MoveBall();
		//ball06->MoveBall();


	}

	

	
	

};