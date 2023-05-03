#pragma once

namespace Tmpl8 {

	class Surface;
	class Ball;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void Colission(Ball* b1, Ball* b2, int _index);
		void CursorVisual(float x, float y);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) { /* implement if you want to handle keys */ }

		void incrementAndOutput(int num, char* output);
	private:
		Surface* screen;
	};

}; // namespace Tmpl8