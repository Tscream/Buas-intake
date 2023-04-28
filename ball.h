#pragma once

namespace Tmpl8 {

	class Ball
	{
	public:
		Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, Surface* _screen, float* _time);
		~Ball();
		void DisplayBall();
		void MoveBall();

		float x;
		float y;
		float radius;
		float vx;
		float vy;
		float mass;
		float gravity = 9.81;
		float resistance = 0.85;

	private:
		Surface* screen{nullptr};
		float time;

		
	};

};