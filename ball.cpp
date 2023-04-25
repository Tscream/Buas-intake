#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"

namespace Tmpl8
{

	float x;
	float y;
	float radius;

	float vx;
	float vy;
	float mass;
	float gravity;
	float resistance = 0.99;

	Surface* screen;

	//Sprite image;

	void Ball::CreateBall(float _xpos, float _ypos, float _radius, Surface* _screen)
	{
		x = _xpos;
		y = _ypos;
		radius = _radius;

		//image.DrawScaled(x, y, 2 * radius, 2 * radius, Game::screen);

		screen = _screen;

		screen->Surface::Bar(100, 100, 500, 500, 0x000000);

		vx = 12;
		vy = -10;
		mass = radius / 50;

	}

	void Ball::DisplayBall()
	{
		gravity = 0.981;

		//image.DrawScaled(x, y, 2 * radius, 2 * radius, Game::screen);
	}

	void Ball::MoveBall()
	{
		//vy = vy + (0.5 * gravity * (t * t));

		//vy = vy + gravity;

		x = x + vx;
		y = y + vy;
		if (x > ScreenWidth - 2 * radius)
		{
			x = ScreenWidth - 2 * radius;
			vx = -vx * resistance;
		}
		if (x < 0)
		{
			x = 0;
			vx = -vx * resistance;
		}
		if (y < 0)
		{
			y = 0;
			vy = -vy * resistance;
		}
		if (y > ScreenHeight - 2 * radius)
		{
			y = ScreenHeight - 2 * radius;
			vy = -vy * resistance;
		}
	}

}