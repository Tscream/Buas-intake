#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"

namespace Tmpl8
{

	// Constructor. This will assign all the values the object needs when you create an instance of this class.
	Ball::Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, float _gravity, Surface* _screen)
	{
		x = _xpos;
		y = _ypos;
		radius = _radius;
		vx = _vx;
		vy = _vy;
		mass = radius / 50;
		gravity = _gravity;
		screen = _screen;
	}

	// The destructor deallocates the resources allocated in the constructor. So basically it frees up the memory taken up by the constructor.
	Ball::~Ball() {};

	// You can write setters and getters if you want to change your values.

	void Ball::DrawLine()
	{
		screen->Bar(100, 100, 500, 500, 0x000000);
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