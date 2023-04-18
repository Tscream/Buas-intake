#include "game.h"
#include "surface.h"
#include "template.h"
#include "iostream"

namespace Tmpl8
{
	vec2 mousePos;
	float viewportWidth;
	float viewportHeight;
	vec2 cursor;

	//walls
	float left;
	float right;
	float top;
	float bottom;

	void Game::MouseMove(int x, int y)
	{

		mousePos.x = mousePos.x + x;
		mousePos.y = mousePos.y + y;
		
		if (mousePos.x > left && mousePos.x < right && mousePos.y > top && mousePos.y < bottom)
		{
			CursorVisual(mousePos.x, mousePos.y);
		}
	}

	void Game::MouseDown(int button)
	{
		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
	}

	void Game::CursorVisual(float x, float y)
	{
		float xPos1 = x - cursor.x / 2;
		float yPos1 = y - cursor.y / 2;
		float xPos2 = x + cursor.x / 2;
		float yPos2 = y + cursor.y / 2;

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0xffffff);

	}

	void Game::DrawViewport()
	{
		//Draw Viewport
		left = ScreenWidth / 2 - viewportWidth / 2;
		top = ScreenHeight / 2 - viewportHeight / 2;
		right = ScreenWidth / 2 + viewportWidth / 2;
		bottom = ScreenHeight / 2 + viewportHeight / 2;

		screen->Line(left, top, left, bottom, 0xffffff); //right wall
		screen->Line(right, top, right, bottom, 0xffffff); //right wall
		screen->Line(left, top, right, top, 0xffffff); //upper wall
		screen->Line(left, bottom, right, bottom, 0xffffff); //bottom wall
	}
	void Game::DrawButtons()
	{
		Button(viewportWidth/2, 250, 100, 30);
	}

	void Game::Button(float posx, float posy, float width, float height)
	{
		screen->Surface::Bar(left + posx - width/2, top + posy - height/2, left + posx + width/2, top + posy + height/2, 0xffffff);
	}


	void Game::Init()
	{
		viewportWidth = 250;
		viewportHeight = 450;

		cursor.x = 20; //visual cursor width
		cursor.y = 20; //visual cursor height
	}
	void Game::Shutdown()
	{
		//save highscore
	}
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0x000000);
		DrawViewport();
		DrawButtons();
	}

	

	
	

};