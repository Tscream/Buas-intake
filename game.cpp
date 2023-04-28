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

	float slomoDebug;


	Ball* ball01{ nullptr };
	Ball* ball02{ nullptr };

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

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0x000000);
	}

	void Game::MouseDown(int button)
	{
		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;

		
	}
	
	void Game::Init()
	{
		cursor.x = 20; //visual cursor width
		cursor.y = 20; //visual cursor height
		DWORD height = GetSystemMetrics(SM_CYSCREEN);
		std::cout << height << std::endl;

		ball01 = new Ball(ScreenWidth / 2, 100, 100, 12, -10, screen, &playTime);
		ball02 = new Ball(ScreenWidth / 2, ScreenHeight - 150, 125, 0, 100, screen, &playTime);
	}

	void Game::Shutdown()
	{
		//save highscore
	}

	void Game::Tick(float deltaTime)
	{
		if (slomoDebug == 0) 
		{
			slomoDebug = 0;

			playTime = playTime + (deltaTime / 1000);

			screen->Clear(0xffffff);

			screen->Bar(ScreenWidth / 2 - 25, ScreenHeight - 125, ScreenWidth / 2 + 25, ScreenHeight - 75, 0xffffff);
			screen->Line(ScreenWidth / 2, ScreenHeight - 100, mousePos.x, mousePos.y, 0x0000ff);


			ball01->DisplayBall();
			ball01->MoveBall();

			if (ball02) {
				ball02->DisplayBall();
				ball02->MoveBall();
			}

			Game::Colission(ball01, ball02);

		}
		else
		{
			slomoDebug++;
		}

	}

	void Game::Colission(Ball* b1, Ball* b2)
	{

		float dx = b2->x - b1->x; //difference in X
		float dy = b2->y - b1->y; //difference in X
		float dist = sqrt(dx * dx + dy * dy); //Pytagoras distance calculation a2 + b2 = c2

		if (dist < b1->radius + b2->radius) //if distance is smaller that the radius of both balls combined it's called collision
		{
			float angle = atan2(dy, dx);
			float _sin = sin(angle);
			float _cos = cos(angle);

			// rotate velocity
			float vx1 = b1->vx * _cos + b1->vy * _sin;
			float vy1 = b1->vy * _cos - b1->vx * _sin;
			float vx2 = b2->vx * _cos + b2->vy * _sin;
			float vy2 = b2->vy * _cos - b2->vx * _sin;

			//resolve 1D velocity, use temp variables
			float vx1final = ((b1->mass - b2->mass) * vx1 + 2 * b2->mass * vx2) / (b1->mass + b2->mass);
			float vx2final = ((b2->mass - b1->mass) * vx2 + 2 * b1->mass * vx1) / (b1->mass + b2->mass);

			// update velocity
			vx1 = vx1final;
			vx2 = vx2final;

			//rotate vel back
			b1->vx = vx1 * _cos - vy1 * _sin;
			b1->vy = vy1 * _cos + vx1 * _sin;
			b2->vx = vx2 * _cos - vy2 * _sin;
			b2->vy = vy2 * _cos + vx2 * _sin;
		}
	}

	

	
	

};