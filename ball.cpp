#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"

namespace Tmpl8
{
	static Sprite ballTexture(new Surface("assets/ball.png"), 1);

	// Constructor. This will assign all the values the object needs when you create an instance of this class.
	Ball::Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, Surface* _screen, float* _deltatime)
	{
		x = _xpos;
		y = _ypos;
		radius = _radius;
		vx = _vx;
		vy = _vy;
		mass = radius * 2;
		screen = _screen;
		deltatimeptr = _deltatime;
	}

	// The destructor deallocates the resources allocated in the constructor. So basically it frees up the memory taken up by the constructor.
	Ball::~Ball()
	{
		std::cout << "Destruct" << std::endl;
	};


	void Ball::DisplayBall()
	{
		ballTexture.DrawScaled(x - radius / 2, y - radius / 2, radius, radius, screen);
		//screen->LoadImage("assets/circle.svg");
	}

	void Ball::MoveTarget()
	{
		vy = vy + (0.5 * gravity) * *deltatimeptr;

		x = x + vx * *deltatimeptr;
		y = y + vy * *deltatimeptr;
		
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
			//wait 1 sec
			vx = 0;
			vy = 0;
			x = ScreenWidth / 2;
			y = 100;
		}
	}

	void Ball::MoveBullet(Ball** elements, int _index) //std::vector<Ball*>* _ballarr
	{
		vy = vy + (0.5 * gravity) * *deltatimeptr;

		x = x + vx * *deltatimeptr;
		y = y + vy * *deltatimeptr;

		std::cout << elements[0] << std::endl;

		std::vector<Ball*> ptr{ *elements };

		if (x > ScreenWidth - radius / 2)
		{
			ptr.erase(ptr.begin() + _index);
		}
		if (x < 0 + radius / 2)
		{
			x = 0 + radius / 2;
			vx = -vx * resistance;
		}
		if (y < 0 + radius / 2)
		{
			ptr.erase(ptr.begin() + _index);

		}
		if (y > ScreenHeight - radius / 2)
		{
			y = ScreenHeight - radius / 2;
			vy = -vy * resistance;
		}
	}

	bool Ball::EndOfLife(float _time)
	{
		currentLifeTime = currentLifeTime + _time / 1000;

		if (currentLifeTime >= lifeTime) 
		{
			return true;
		}
		return false;
	}

}