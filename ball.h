#pragma once
#include "vector"

namespace Tmpl8 {

	class Ball
	{
	public:
		Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, Surface* _screen, float* _time);
		~Ball();
		void DisplayBall();
		void MoveTarget();
		void MoveBullet(Ball** elements, int _index);
		bool EndOfLife(float _time);

		float x;
		float y;
		float radius;
		float vx;
		float vy;
		float mass;
		float gravity = 9.81;
		float resistance = 0.85;
		float lifeTime = 2;
		

	private:
		Surface* screen{nullptr};
		float* deltatimeptr;
		float currentLifeTime = 0;

		
	};

};