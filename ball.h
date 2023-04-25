#pragma once

namespace Tmpl8 {

	class Ball
	{
	public:
		Ball(float _xpos, float _ypos, float _radius, float _vx, float _vy, float _gravity, Surface* _screen);
		~Ball();
		/*void CreateBall(float _xpos, float _ypos, float _radius, Surface* _screen);
		void DisplayBall();*/
		void DrawLine();
		void MoveBall();
	private:
	Surface* screen;
	float x;
	float y;
	float radius;

	float vx;
	float vy;
	float mass;
	float gravity;
	float resistance = 0.99;
	};

};