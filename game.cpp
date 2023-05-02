#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"
#include "vector"
#include <Windows.h>

namespace Tmpl8
{
	vec2 mousePos;
	vec2 mouseSize;
	vec2 turretPos;
	vec2 turretSize;
	float bulletSpeed;
	float shootCooldown;
	float playTime = 0;
	float deltatime = 0;
	float slomoDebug;

	Ball* target;
	std::vector<Ball*> balls;

	void Game::MouseMove(int x, int y)
	{
		mousePos.x = mousePos.x + x;
		mousePos.y = mousePos.y + y;
		
		if (mousePos.x > 0 + mouseSize.x/2 && mousePos.x < ScreenWidth - mouseSize.x/2 && mousePos.y > 0 + mouseSize.y/2 && mousePos.y < ScreenHeight - mouseSize.y/2)
		{
			CursorVisual(mousePos.x, mousePos.y);
		}
	}

	void Game::CursorVisual(float x, float y)
	{
		float xPos1 = x - mouseSize.x / 2;
		float yPos1 = y - mouseSize.y / 2;
		float xPos2 = x + mouseSize.x / 2;
		float yPos2 = y + mouseSize.y / 2;

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0xffffff);
	}

	void Game::MouseDown(int button)
	{
		if (playTime < shootCooldown) { return; }
		shootCooldown = playTime + 0.5;
		float vx = mousePos.x - turretPos.x;
		float vy = mousePos.y - turretPos.y;
		float dist = sqrt(vx * vx + vy * vy);

		float vxnormal = vx / dist;
		float vynormal = vy / dist;

		balls.push_back(new Ball(turretPos.x, turretPos.y, 50, 1, vxnormal * bulletSpeed, vynormal * bulletSpeed, screen, &playTime, &deltatime));

	}
	
	void Game::Init()
	{
		mouseSize = { 20,20 };
		turretPos = { ScreenWidth / 2 ,ScreenHeight - 100 };
		turretSize = { 50,50 };
		bulletSpeed = 15;


		DWORD height = GetSystemMetrics(SM_CYSCREEN);
		std::cout << height << std::endl;

		target = new Ball(ScreenWidth / 2, 100, 125, 1, 0, 0, screen, &playTime, &deltatime);
	}

	void Game::Shutdown()
	{
		//save highscore
	}

	void Game::Tick(float _deltaTime)
	{
		if (slomoDebug == 0)
		{
			slomoDebug = 0;

			playTime = playTime + _deltaTime / 1000;
			
			deltatime = _deltaTime / 1000;

			screen->Clear(0x000000);


			for (int i = 0; i < balls.size(); i++)
			{
				balls[i]->MoveBullet();

				if (balls[i]->EndOfLife()) {
					balls.erase(balls.begin() + i);
					return;
				}
				
				balls[i]->DisplayBall();
				
				if (balls.size() >= 1)
				{
					Game::Colission(target, balls[i], i);
				}

			}

			target->MoveTarget();
			target->DisplayBall();

			//screen->Bar(0, ScreenHeight - 150, ScreenWidth, ScreenHeight - 1, 0xff00ff); //bar
			screen->Bar(turretPos.x - turretSize.x / 2, turretPos.y - turretSize.y / 2, turretPos.x + turretSize.x / 2, turretPos.y + turretSize.y / 2, 0xffffff); //turret

			screen->Line(ScreenWidth / 2, ScreenHeight - 100, mousePos.x, mousePos.y, 0x0000ff); //line from turret to mouse
		}
		else
		{
			slomoDebug++;
		}
	}

	void Game::Colission(Ball* b1, Ball* b2, int _index)
	{
		float dx = b2->x - b1->x; //difference in X
		float dy = b2->y - b1->y; //difference in X
		float dist = sqrt(dx * dx + dy * dy); //Pytagoras distance calculation a2 + b2 = c2

		screen->Line(b1->x, b1->y, b2->x, b2->y, 0x00ff00);

		if (dist < b1->radius / 2 + b2->radius / 2) //if distance is smaller that the radius of both balls combined it's called collision
		{
			float angle = atan2(dy, dx);
			float _sin = sin(angle);
			float _cos = cos(angle);

			float x1 = 0;
			float y1 = 0;
			float x2 = dx * _cos + dy * _sin;
			float y2 = dy * _cos + dx * _sin;

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

			/*float absVelocity = abs(vx1) + abs(vx2);
			float overlap = (b1->radius + b2->radius) - abs(x1 - x2);
			x1 += vx1 / absVelocity * overlap;
			x2 += vx2 / absVelocity * overlap;


			float x1final = x1 * _cos - y1 * _sin;
			float y1final = y1 * _cos + x1 * _sin;
			float x2final = x2 * _cos - y2 * _sin;
			float y2final = y2 * _cos + x2 * _sin;*/


			// finally compute the new absolute positions
			/*b2->x = b1->x + x2final;
			b2->y = b1->y + y2final;

			b1->x = b1->x + x1final;
			b1->y = b1->y + y1final;*/


			//rotate vel back
			b1->vx = vx1 * _cos - vy1 * _sin;
			b1->vy = vy1 * _cos + vx1 * _sin;
			b2->vx = vx2 * _cos - vy2 * _sin;
			b2->vy = vy2 * _cos + vx2 * _sin;

			balls.erase(balls.begin() + _index);
		}
	}

	

	
	

};