#pragma once
#include "vector"

namespace Tmpl8 {

	class Ball
	{
	public:
		Ball(float _xpos, float _ypos, float _radius, float _mass, float _vx, float _vy, Surface* _screen, float* _time, float* _delta);
		~Ball();
		void DisplayBall();
		void MoveTarget();
		void MoveBullet();
		bool EndOfLife();

		float x;
		float y;
		float radius;
		float vx;
		float vy;
		float mass;
		float gravity = 9.81;
		float resistance = 0.85;
		float spawnTime;
		float lifespan = 5;
		float currentLifeTime = 0;
		const float physicsScaler = 75; //multiplies all physics with 50 so that it's 75 pixels per 'meter'
		

	private:
		Surface* screen{nullptr};
		float* timeptr;
		float* deltaptr;

		
	};

};