///////////////////////////////////////////////////////////////////////////////
// GameObjects.cpp
// ===========
// This file implements the core game objects used in animation including
// Brick, Paddle, and Circle. Each class defines its behavior and rendering
// logic for their intended game use. Bricks can be destructible or reflective.
// The paddle is controlled by the playerm and circles move and interact with
// the paddle and bricks with physics-based collisions.
//
// Objects:
// -------------
// - Brick: Handles rendering and hit logic for all bricks
// - Paddle: Inherits from brick, allowing left/right movement
// - Circle: Handles ball movement, screen collisions, and object interaction
//
// Author: Caleb Luplow
// Date: 6/24/2025
// Assignment: 8-2 Assignment - CS-330 Computational Graphics and Visualization
///////////////////////////////////////////////////////////////////////////////

#include "GameObjects.h"
#include <stdlib.h>
#include <vector>
#include "constants.h"


/**
*  Brick constuctor.
*  Initializes the brick with its type, position, size, color, and hit points.
* 
*  @param bt Type of brick (REFLECTIVE or DESTRUCTIBLE)
*  @param xx X-coordinate of the brick center
*  @param yy Y-coordinate of the brick cetner
*  @param ww Width of the brick
*  @param hh Height of the brick
*  @param rr Red color value (0.0 - 1.0)
*  @param gg Green color value (0.0 - 1.0)
*  @param bb Blue color value (0.0 - 1.0)
*  @param hp Hit points
*/
Brick::Brick(BRICKTYPE bt, float xx, float yy,
	float ww, float hh,
	float rr, float gg, float bb,
	int hp)
{
	brick_type = bt;
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	red = rr;
	green = gg;
	blue = bb;
	hitPoints = hp;
	onoff = ON;
}

/**
*  Renders bricks to the screen if its state is ON.
*  Draws the brick as a rectangle based on its current color and size.
*/
void Brick::drawBrick()
{
	if (onoff == ON)
	{
		double halfW = width / 2;
		double halfH = height / 2;

		glColor3d(red, green, blue);
		glBegin(GL_POLYGON);

		glVertex2d(x + halfW, y + halfH);
		glVertex2d(x + halfW, y - halfH);
		glVertex2d(x - halfW, y - halfH);
		glVertex2d(x - halfW, y + halfH);

		glEnd();
	}
}

/**
*  Handles collision damage to a brick.
*  Reduces hit points and updates color based on remaining health.
*  When hit points become 0, the brick state is changed to OFF.
*/
void Brick::takeHit()
{
	if (hitPoints <= 0) return;

	--hitPoints;

	switch (hitPoints)
	{
	case 2:					// Yellow brick
		red = COLOR_YELLOW[0];
		green = COLOR_YELLOW[1];
		blue = COLOR_YELLOW[2];
		break;

	case 1:					// Green Brick
		red = COLOR_GREEN[0];
		green = COLOR_GREEN[1];
		blue = COLOR_GREEN[2];
		brick_type = DESTRUCTIBLE;
		break;


	case 0:					// Dead brick
		onoff = OFF;
		break;
	}
}


/**
*  Paddle constructor
*  Initializes a player controlled paddle using brick properties and
*  assigns movement speed.
* 
*  @param xx X-coordinate of the paddle's center
*  @param yy Y-coordinate of the paddle's center
*  @param ww Width of the paddle
*  @param hh Height of the paddle
*  @param r Red color value (0.0 - 1.0)
*  @param g Green color value (0.0 - 1.0)
*  @param b Blue color value (0.0 - 1.0)
*/
Paddle::Paddle(float xx, float yy,
	float ww, float hh,
	float r, float g, float b)
	: Brick(REFLECTIVE, xx, yy, ww, hh, r, g, b)
{
	speed = 0.9f;
}

/**
*  Moves the paddle left based on its speed and delta time.
* 
*  @param dt Delta time to ensure frame-rate independent movement.
*/
void Paddle::moveLeft(float dt)
{
	float newSpeed = speed * dt;
	if (x - width / 2 > -1) x -= newSpeed;
}

/**
*  Moves the paddle right based on its speed and delta time.
*
*  @param dt Delta time to ensure frame-rate independent movement.
*/
void Paddle::moveRight(float dt)
{
	float newSpeed = speed * dt;
	if (x + width / 2 < 1) x += newSpeed;
}


/**
*  Circle constructor
*  Initializes circle (ball) at the given position and gives
*  it a random movement direction.
* 
*  @param xx X-coordinate of the circle's center.
*  @param yy Y-coordinate of the circle's center.
*  @param rad Radius of the circle.
*  @param r Red color value (0.0 - 1.0)
*  @param g Green color value (0.0 - 1.0)
*  @param b Blue color value (0.0 - 1.0)
*/
Circle::Circle(double xx, double yy, float rad,
	float r, float g, float b)
{
	x = xx;
	y = yy;
	red = r;
	green = g;
	blue = b;
	radius = rad;

	// Random angle
	float angle = ((rand() % 360) * DEG2RAD);

	// Set velocity with angle and speed
	vx = cos(angle) * speed;
	vy = sin(angle) * speed;
}

/**
*  Checks for and responds to collisions between the circle and brick.
*  Handles paddle deflection logic, wall deflection, and changes the
*  brick state based on its type.
* 
*  @param brk Pointer to the brick to check a collision with
*/
void Circle::CheckCollision(Brick* brk)
{
	// Ignore destroyed bricks
	if (brk->onoff == OFF) return;

	// Variables to find brick edges
	float halfW = brk->width / 2;
	float halfH = brk->height / 2;

	// Check if the circle overlaps the edge of the brick
	if ((x + radius > brk->x - halfW) && (x - radius < brk->x + halfW) &&
		(y + radius > brk->y - halfH) && (y - radius < brk->y + halfH))
	{
		// Collision logic for the paddle
		if (brk == static_cast<Brick*>(&paddle))
		{
			if (vy < 0)
			{
				float normalizedHit = (x - brk->x) / (brk->width / 2.0f);

				// Normalize the hit variable
				if (normalizedHit < -1.0f) normalizedHit = -1.0f;
				else if (normalizedHit > 1.0f) normalizedHit = 1.0f;

				// The ball bounces relative to the angle of the hit
				float bounceAngle = normalizedHit * (60 * DEG2RAD);
				float newSpeed = sqrt(vx * vx + vy * vy); // Preserves speed

				vx = newSpeed * sin(bounceAngle);
				vy = newSpeed * abs(cos(bounceAngle));

				y = brk->y + brk->height / 2 + radius + 0.001f; // Nudge the ball
			}

			return;
		}

		// Brick collisions
		// Determine which side of the brick was impacted from brick center
		float dx = x - brk->x;
		float dy = y - brk->y;

		// Calculate circle overlap
		float overlapX = (radius + halfW) - fabs(dx);
		float overlapY = (radius + halfH) - fabs(dy);

		// Compare overlap to determine primary impact
		if (overlapX < overlapY)
		{
			// Left and right collisions
			vx *= -1;
			x += (dx > 0 ? overlapX : -overlapX);
		}
		else
		{
			// Top and bottom collisions
			vy *= -1;
			y += (dy > 0 ? overlapY : -overlapY);
		}

		// Destroy a brick
		if (brk->brick_type == DESTRUCTIBLE)
		{
			brk->onoff = OFF;
		}
		// Subtract brick HP
		else
		{
			brk->takeHit();
		}
	}
}

/**
*  Generates a random integer direction from 1 to 8 for initial
*  circle movement.
* 
*  @return Integer representing a direction (1-8)
*/
int Circle::GetRandomDirection()
{
	return (rand() % 8) + 1;
}

/**
*  Moves the circle forward by one step based on its velocity and delta time.
*  Also handles boundary collisions with the sides and top edges.
* 
*  @param dt Delta time to scale movement
*/
void Circle::MoveOneStep(float dt)
{
	// Apply deltaTime
	float newX = x + vx * dt;
	float newY = y + vy * dt;

	// Bouce left and right
	if (newX - radius < -1.0f || newX + radius > 1.0f)
		vx *= -1;

	// Bounce off top
	if (newY + radius > 1.0f)
		vy *= -1;

	x += vx * dt;
	y += vy * dt;
}

/**
*  Renders the circle to the screen using OpenGL.
*/
void Circle::DrawCircle()
{
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
	}
	glEnd();
}
