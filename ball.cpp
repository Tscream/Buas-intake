#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"
#include "vector"

namespace Tmpl8
{
	static Sprite ballTexture(new Surface("assets/ball.png"), 1);

	// Constructor. This will assign all the values the object needs when you create an instance of this class.
	Ball::Ball(float _xpos, float _ypos, float _radius, float _mass, float _vx, float _vy, Surface* _screen, float* _time, float* _delta)
	{
		x = _xpos;
		y = _ypos;
		radius = _radius;
		vx = _vx;
		vy = _vy;
		mass = _mass;
		screen = _screen;
		timeptr = _time;
		spawnTime = *timeptr;
		deltaptr = _delta;
	}

	// The destructor deallocates the resources allocated in the constructor. So basically it frees up the memory taken up by the constructor.
	Ball::~Ball()
	{
		std::cout << "Destruct" << std::endl;
	};

	void Ball::DisplayBall()
	{
		ballTexture.DrawScaled(x - radius / 2, y - radius / 2, radius, radius, screen);
		currentLifeTime = *timeptr - spawnTime;
		//screen->LoadImage("assets/circle.svg");
	}

	void Ball::MoveTarget()
	{
		vy = vy + (0.5 * gravity) * *deltaptr;

		x = x + vx * *deltaptr * physicsScaler;
		y = y + vy * *deltaptr * physicsScaler;

		if (x > ScreenWidth - radius / 2)
		{
			x = ScreenWidth - radius / 2;
			vx = -vx * resistance;
		}
		if (x < 0 + radius / 2)
		{
			x = 0 + radius / 2;
			vx = -vx * resistance;
		}
		if (y < 0 + radius / 2)
		{
			y = 0 + radius / 2;
			vy = -vy * resistance;
		}
		if (y > ScreenHeight - radius / 2)
		{
			y = ScreenHeight - radius / 2;
			vy = -vy * resistance;

			vx = 0;
			vy = 0;
			x = ScreenWidth / 2;
			y = 100;
			//gameover()
			//wait 1 sec
		}
	}

	void Ball::MoveBullet()
	{
		vy = vy + *deltaptr;

		x = x + vx * *deltaptr * physicsScaler;
		y = y + vy * *deltaptr * physicsScaler;

		y = y + vy * *deltaptr;

		if (x > ScreenWidth - radius / 2)
		{
			x = ScreenWidth - radius / 2;
			vx = -vx * resistance;
		}
		if (x < 0 + radius / 2)
		{
			x = 0 + radius / 2;
			vx = -vx * resistance;
		}
	}

	bool Ball::EndOfLife()
	{
		if (currentLifeTime >= lifespan || y < 0 + radius / 2 || y > ScreenHeight - radius / 2)
		{
			/*y = 0 + radius / 2;
			vy = -vy * resistance;*/
			return true;
		}
		return false;
	}

}