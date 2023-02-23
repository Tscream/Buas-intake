#include "game.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	const vec2 position = { 100, 100 };
	struct Foo
	{
		vec2 targetPoint;
		Pixel color;
	};

	const Foo lineinfo[] = {
		{ {100 ,100 }	, 0xFFFF0000},
		{ {0 ,100}		, 0xFF00FF00},
		{ {50,50}		, 0xFF0000FF},
	};

	void Game::Init()
	{
		
	}
	
	void Game::Shutdown()
	{
	}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0x00000000);

		vec2 beginPos = { 50,50 };

		for(const Foo line : lineinfo)
		{
			screen->Line(beginPos.x + position.x ,beginPos.y + position.y, line.targetPoint.x + position.x, line.targetPoint.y + position.y, line.color);
			beginPos = { line.targetPoint.x, line.targetPoint.y };
		}

	}
};