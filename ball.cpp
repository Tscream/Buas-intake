#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"
#include "vector"

namespace Tmpl8
{
	//get the ball texture
	static Sprite ballTexture(new Surface("assets/ballhighres.png"), 1);

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
	}

	void Ball::MoveTarget()
	{
		vy = vy + (0.5 * gravity) * *deltaptr; //calculates the y velocity of the ball by adding gravity

		x = x + vx * *deltaptr * physicsScaler; //adds the velocity to the x axis en multiplies by the physics scaler because the formulas are pixels per second instead of meters per second
		y = y + vy * *deltaptr * physicsScaler; //adds the velocity to the y axis en multiplies by the physics scaler because the formulas are pixels per second instead of meters per second

		if (x > ScreenWidth - radius / 2) //check if target hit right side of screen
		{
			x = ScreenWidth - radius / 2;
			vx = -vx * resistance;
		}
		if (x < 0 + radius / 2) //check if target hit left side of screen
		{
			x = 0 + radius / 2;
			vx = -vx * resistance;
		}
		if (y < 0 + radius / 2) //check if target hit top of screen
		{
			y = 0 + radius / 2;
			vy = -vy * resistance;
		}
		if (y > ScreenHeight - radius / 2 - 150) //check if target hit bottom of screen
		{
			y = ScreenHeight - radius / 2 - 140;
			vy = -vy * resistance;

			vx = 0; //reset the velocity
			vy = 0;
			x = ScreenWidth / 2; //recentre it on the x axis
			y = 120; //set y position at top of screen
			game->AddScore(0); //reset score by parsing 0
		}
	}

	void Ball::MoveBullet()
	{
		vy = vy + *deltaptr; //calculates the y velocity of the ball by adding gravity

		x = x + vx * *deltaptr * physicsScaler; //adds the velocity to the x axis en multiplies by the physics scaler because the formulas are pixels per second instead of meters per second
		y = y + vy * *deltaptr * physicsScaler; //adds the velocity to the y axis en multiplies by the physics scaler because the formulas are pixels per second instead of meters per second

		if (x > ScreenWidth - radius / 2) //check if bullet hit right side of screen
		{
			x = ScreenWidth - radius / 2;
			vx = -vx * resistance;
		}
		if (x < 0 + radius / 2) //check if bullet hit left side of screen
		{
			x = 0 + radius / 2;
			vx = -vx * resistance;
		}
	}

	bool Ball::EndOfLife()
	{
		if (currentLifeTime >= lifespan || y < 0 + radius / 2 || y > ScreenHeight - radius / 2) //check if bullet is older then 5 seconds or hit top of screen or hit bottom of screen 
		{
			return true;
		}
		return false;
	}

}