///////////////////////////////////////////////////////////////////////////////
// GameObjects.h
// ===========
// Header file containing the game object class definitions used in this game.
//
// Objects:
// -------------
// - Brick: Static or destructible objects with hit points and colors
// - Paddle: Player controlled object derived from Brick.
// - Circle: A moving object that represents the ball and handles collisions
//
// Author: Caleb Luplow
// Date: 3/26/2026
// Assignment: CS-499 Capstone - CS-330 Coding Collisions Enhancement
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GLFW/glfw3.h>
#include "constants.h"

// ==========================
// Brick Class
// Represents a single brick with color, size, type, and a hit point state.
// ==========================
class Brick
{
public:
	float red, green, blue;		// Color
	float x, y;					// Center position
	float width, height;		// Size
	int hitPoints;				// 3-Red, 2-Yellow, 1-Green, 0-gone
	BRICKTYPE brick_type;		// REFLECTIVE or DESTRUCTIBLE
	ONOFF onoff;				// Visibility for bricks


	// Constructor
	Brick(BRICKTYPE bt, float xx, float yy,
		float ww, float hh,
		float rr, float gg, float bb,
		int hp = 0);


	void drawBrick();			// Draws the brick to the screen
	void takeHit();				// Handles damage to the brick object
};


// ==========================
// Paddle Class
// The player controlled object derived from a brick that moves left and right.
// ==========================
class Paddle : public Brick
{
public:
	float speed;				// Movement speed


	// Constructor
	Paddle(float xx, float yy,
		float ww = 0.4f, float hh = 0.05f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f);


	void moveLeft(float dt);
	void moveRight(float dt);
};


// ==========================
// Circle Class
// Represents a moving ball with physics logic and collision handling.
// ==========================
class Circle
{
public:
	float red, green, blue;		// Color
	float radius;				// Size
	float x, y;					// Center position
	float speed = 1;			// Ball speed
	float vx, vy;				// X and Y velocities


	// Constructor
	Circle(double xx, double yy, float rad,
		float r, float g, float b);

	void CheckCollision(Brick* brk);	// Checks circle collisions with screen bounds and objects
	int GetRandomDirection();			// Chooses a random travel direction on ball spawn
	void MoveOneStep(float dt);			// Moves the circle based on its velocity and handles screen boundary collisions
	void DrawCircle();					// Draws the circle to the screen
};

