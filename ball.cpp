#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"

namespace Tmpl8
{
	static Sprite ballTexture(new Surface("assets/ball.png"), 1);
	float* ptr;

	// Constructor. This will assign all the values the object needs when you create an instance of this class.
	Ball::Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, Surface* _screen, float* _time)
	{
		x = _xpos;
		y = _ypos;
		radius = _radius;
		vx = _vx;
		vy = _vy;
		mass = radius / 50;
		screen = _screen;
		ptr = _time;
		

	}

	// The destructor deallocates the resources allocated in the constructor. So basically it frees up the memory taken up by the constructor.
	Ball::~Ball() {};



	void Ball::DisplayBall()
	{
		ballTexture.DrawScaled(x, y, radius, radius, screen);

		std::cout << *ptr / 1000 << std::endl;
	}

	void Ball::MoveBall()
	{
		//vy = vy + (0.5 * gravity * (t * t));

		//vy = vy + gravity;

		x = x + vx;
		y = y + vy;
		if (x > ScreenWidth - radius)
		{
			x = ScreenWidth - radius;
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
		if (y > ScreenHeight - radius)
		{
			y = ScreenHeight - radius;
			vy = -vy * resistance;
		}
	}
}