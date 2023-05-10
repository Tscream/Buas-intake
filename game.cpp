#include "game.h"
#include "surface.h"
#include "template.h"
#include "ball.h"
#include "iostream"
#include "vector"
#include <Windows.h>
#include <sstream>

namespace Tmpl8
{
	vec2 mousePos; //position of mouse on sreen
	vec2 mouseSize; //mouse visual size (only used for debugging)
	vec2 turretPos; //position of turret on screen
	vec2 turretSize; //turret visual size
	float barHeight; //the height of the bottom bar
	float bulletSpeed;
	float shootCooldown; //the time before the next bullet can be fired
	float playTime = 0; //how long is the game running for
	float deltatime = 0; //the time between 2 frames
	float scoreSize; //the font size of the score
	int score; //the score itself
	int highscore; //the highest score this play sesion
	char* scoreText;
	char* highscoretext;

	Ball* target; //constructor of the larger ball (target)
	std::vector<Ball*> balls; //an array with a variable length containing the constructor of the smaler ball (bullets)

	void Game::MouseMove(int x, int y) //this runs every time the mouse moves
	{
		mousePos.x = mousePos.x + x; //adds up the amout it moved to the old mouse position to get the current mouse position
		mousePos.y = mousePos.y + y;

		//This was used to debug my code and to see the mouse position in game
		if (mousePos.x > 0 + mouseSize.x / 2 && mousePos.x < ScreenWidth - mouseSize.x / 2 && mousePos.y > 0 + mouseSize.y / 2 && mousePos.y < ScreenHeight - mouseSize.y / 2)
		{
			//CursorVisual(mousePos.x, mousePos.y);
		}
	}

	void Game::CursorVisual(float x, float y) //gives a visual positon on the screen
	{
		float xPos1 = x - mouseSize.x / 2; //centre the square on the position of the mouse
		float yPos1 = y - mouseSize.y / 2;
		float xPos2 = x + mouseSize.x / 2;
		float yPos2 = y + mouseSize.y / 2;

		screen->Surface::Bar(xPos1, yPos1, xPos2, yPos2, 0xffffff);
	}

	void Game::MouseDown(int button) //this runs when a mouse button is pressed
	{
		if (playTime < shootCooldown) { return; } //check if player can already shoot otherwise canncel
		shootCooldown = playTime + 0.5; //adds 0.5 seconds to cooldown
		float vx = mousePos.x - turretPos.x; //gets the difference in x
		float vy = mousePos.y - turretPos.y; //gets the difference in y
		float dist = sqrt(vx * vx + vy * vy); //uses pythagoras theorem to calculate distance

		float vxnormal = vx / dist; //normalize the direction
		float vynormal = vy / dist;

		//constructs a new ball with a specific position, size, mass and directional speed and gives the memory addres of the current play time
		balls.push_back(new Ball(turretPos.x, turretPos.y, 50, 1, vxnormal * bulletSpeed, vynormal * bulletSpeed, screen, &playTime, &deltatime)); 

	}

	void Game::AddScore(int i = 1) //this runs when the score needs to be updated, by default it adds up 1 point but when zero it means it has to update the highscore
	{
		if (i == 0) {
			if (highscore < score) { //checks if current score is higher then high score
				highscore = score; //makes the high score the current score
				std::string str;

				if (score < 10) {
					str = "High score: 0" + std::to_string(highscore); //some string formatting adds a 0 when the score is lower the 10
				}
				else 
				{
					str = "High score: " + std::to_string(highscore); //some string formating
				}

				highscoretext = new char[str.length()]; //make a char array the size of string

				std::strcpy(highscoretext, str.c_str()); //copy the string over to the char array

				highscoretext[str.length()] = '\0';	//empties the char array
			}

			score = 0;
			
		}


		score = score + i; //adds the score

		///summary
		///pretty much the same code as above but this time for the score itself 
		/// 

		std::string str;

		if (score < 10) {
			str = "0" + std::to_string(score);
		}
		else
		{
			str = std::to_string(score);
		}

		scoreText = new char[str.length()];

		std::strcpy(scoreText, str.c_str());

		scoreText[str.length()] = '\0';
	}

	void Game::Colission(Ball* b1, Ball* b2, int _index) //checks for collision between target and all other bullets
	{
		float dx = b2->x - b1->x; //difference in X
		float dy = b2->y - b1->y; //difference in X
		float dist = sqrt(dx * dx + dy * dy); //Pytagoras distance calculation a2 + b2 = c2

		if (dist < b1->radius / 2 + b2->radius / 2) //if distance is smaller that the radius of both balls combined it's called collision
		{
			float angle = atan2(dy, dx); //calculates the angle where the balls collide
			float _sin = sin(angle); //calculate how much force on the x
			float _cos = cos(angle); //calculate how much force on the y

			float x1 = 0;
			float y1 = 0;
			float x2 = dx * _cos + dy * _sin;
			float y2 = dy * _cos + dx * _sin;

			// rotate velocity so it's 1D and easier to understand
			float vx1 = b1->vx * _cos + b1->vy * _sin;
			float vy1 = b1->vy * _cos - b1->vx * _sin;
			float vx2 = b2->vx * _cos + b2->vy * _sin;
			float vy2 = b2->vy * _cos - b2->vx * _sin;

			//solve velocity in 2D
			float vx1final = ((b1->mass - b2->mass) * vx1 + 2 * b2->mass * vx2) / (b1->mass + b2->mass);
			float vx2final = ((b2->mass - b1->mass) * vx2 + 2 * b1->mass * vx1) / (b1->mass + b2->mass);

			// update velocity
			vx1 = vx1final;
			vx2 = vx2final;

			//adds the velocity of the collision back to the balls
			b1->vx = vx1 * _cos - vy1 * _sin;
			b1->vy = vy1 * _cos + vx1 * _sin;
			b2->vx = vx2 * _cos - vy2 * _sin;
			b2->vy = vy2 * _cos + vx2 * _sin;

			Game::AddScore(); //add a score

			balls.erase(balls.begin() + _index); //remove the ball that collided using index
		}
	}

	void Game::Init()
	{
		mouseSize = { 20,20 }; //set the size of the mouse
		barHeight = 150; //set the height of the bottom bar
		turretSize = { 50,50 }; //set the size of the turret
		turretPos = { ScreenWidth / 2 ,ScreenHeight - barHeight / 2 }; //set the turrets position
		bulletSpeed = 15; //set the speed of the bullets
		scoreSize = 25; //set the font size of the score
		scoreText = "00"; //set the initial score
		highscoretext = "High score: 00"; //set the initial highscore

		DWORD height = GetSystemMetrics(SM_CYSCREEN);
		std::cout << "The height of your screen is " << height << " pixels" << std::endl; 
		//I wanted to add a automatic full screen option by getting the pixel height of the screen but I couldn't get acces to the screenheight varible in template.h because it was const

		target = new Ball(ScreenWidth / 2, 100, 125, 1, 0, 0, screen, &playTime, &deltatime); //when te game is all set it spawns the target at the top of the screen
	}

	void Game::Shutdown() {}

	void Game::Tick(float _deltaTime)
	{
		playTime = playTime + _deltaTime / 1000; //it calulates the current time that game has been running

		deltatime = _deltaTime / 1000; //calculates the time between frames

		screen->Clear(0x000000); //clears the screen

		screen->Print(scoreText, ScreenWidth / 2 - scoreSize * 5.5, ScreenHeight / 2 - scoreSize * 2.5 - barHeight, 0xffffff, scoreSize); //draws the current score on screen

		target->MoveTarget(); //calculate the target ball position
		target->DisplayBall(); //draws the target ball on that position

		screen->Bar(0, ScreenHeight - barHeight, ScreenWidth, ScreenHeight - 1, 0xffffff); //draws bottom bar
		
		screen->Print(highscoretext, 10, ScreenHeight - 30, 0xff0000, 3); //draws the highscore on the bottom bar
		screen->Print("Left click to shoot,", 10, 10, 0xffffff, 3); //draws instructions in the top left corner of the screen
		screen->Print("try and hold the ball up!", 10, 35, 0xffffff, 3);

		for (int i = 0; i < balls.size(); i++) //loops over every bullet thats currently in the game
		{
			balls[i]->MoveBullet(); //calculate the bullets ball position

			if (balls[i]->EndOfLife()) //check if the bullet hit the top or bottom of the screen
			{ 
				balls.erase(balls.begin() + i); //if so then remove that bullet
				return;
			}

			balls[i]->DisplayBall();  //draws the bullets ball on that position

			if (balls.size() >= 1) //check if there are any bullets in the game
			{
				Game::Colission(target, balls[i], i); //if so check for collision
			}
		}

		DrawBarrel(20, 50); //draw the barrel of the turret
		screen->Bar(turretPos.x - turretSize.x / 2, turretPos.y - turretSize.y / 2, turretPos.x + turretSize.x / 2, turretPos.y + turretSize.y / 2, 0x0000ff); //draw the turret itself

		//screen->Line(ScreenWidth / 2, 0, ScreenWidth / 2, ScreenHeight, 0xffff00); //debug code to check where the centre is
		//screen->Line(0, ScreenHeight/2, ScreenWidth, ScreenHeight/2, 0xffff00);
	}

	void Game::DrawBarrel(int _thicness, float _length) //draws the barrel
	{

		float vx = mousePos.x - turretPos.x;
		float vy = mousePos.y - turretPos.y;
		float dist = sqrt(vx * vx + vy * vy);

		float vxnormal = vx / dist;
		float vynormal = vy / dist;

		for (int i = 0; i < _thicness; i++) //loops over how thic the barrel needs to be and draws a line to that position
		{
			screen->Line(ScreenWidth / 2 + i / 2,	 ScreenHeight - 100,		 ScreenWidth / 2 + (vxnormal * _length) + i / 2,		ScreenHeight - 100 + (vynormal * _length), 0xff0000);
			screen->Line(ScreenWidth / 2 - i / 2,	 ScreenHeight - 100,		 ScreenWidth / 2 + (vxnormal * _length) - i / 2,		ScreenHeight - 100 + (vynormal * _length), 0xff0000);
		}
	}

};