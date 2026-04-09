///////////////////////////////////////////////////////////////////////////////
// 2D Game Program
// ===============
// This program implements a simple 2D game using OpenGL and GLFW. The game
// involves circular objects (referred to as "balls") that move within a window 
// and interact with static rectangular bricks. The primary features of the game
// include:
// 
// - **Bricks**: Represented as either reflective or destructible. Reflective 
//   bricks change the direction of the balls upon collision, while destructible
//   bricks disappear when hit.
// - **Balls**: Circular objects that move randomly within the window. Their 
//   motion is influenced by collisions with bricks and window boundaries.
// - **Input Handling**: Players can spawn new balls by pressing the spacebar or 
//   close the game window by pressing the ESC key.
//
// Key Features:
// -------------
// - **Brick Types**:
//   - Bricks alter the direction of the balls.
//   - Red, yellow, and green bricks have 3, 2, and 1 HP respectively.
//	 - Green bricks disappear on hit
// - **Ball Motion**:
//   - Spawned balls initially move in a random direction.
//   - Balls move in respect to the angle it hits.
//   - Collisions with bricks are handled dynamically.
//   - Balls are destroyed on impact with one another.
//   - Balls are destroyed when they disappear on the bottom of the playing area.
// - **User Input**:
//   - Spacebar spawns a new ball at the center with random colors.
//   - Left and Right keys move the paddle side to side.
//   - ESC closes the application.
// 
// Dependencies:
// -------------
// - GLFW for window creation and input handling.
// - OpenGL for rendering graphics.
// 
// Author: Caleb Luplow
// Date: 3/26/2026
// Assignment: CS-499 Capstone - CS-330 Coding Collisions Enhancement
///////////////////////////////////////////////////////////////////////////////

#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

#include "constants.h"
#include "GameObjects.h"
#include "Utilities.h"


using namespace std;


Paddle paddle(0.0f, 0.0f);

vector<Brick> brickGrid;
vector<Circle> world;

bool isPressed = false;


int main(void) {
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(800, 800, "DSA Enhancement - Luplow", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	GenerateBrickGrid(brickGrid,
		8, 10,				// Rows, Cols
		0.15f, 0.05f,		// Brick size
		0.02f, 0.02f);		// X and Y spacing

	paddle = Paddle(0.0f, -0.9f);

	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		SetupScene(width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		ProcessInput(window, deltaTime);

		vector<bool> toDestroy(world.size(), false);

		for (size_t i = 0; i < world.size(); ++i)
		{
			for (size_t j = i + 1; j < world.size(); ++j)
			{
				float dx = world[j].x - world[i].x;
				float dy = world[j].y - world[i].y;
				float rSum = world[i].radius + world[j].radius;
				if (dx * dx + dy * dy < rSum * rSum)
				{
					toDestroy[i] = toDestroy[j] = true;
				}
			}
		}

		for (size_t i = 0; i < world.size();)
		{
			if (toDestroy[i])
			{
				world.erase(world.begin() + i);
				toDestroy.erase(toDestroy.begin() + i);
				continue;
			}

			Circle& ball = world[i];

			ball.CheckCollision(&paddle);

			for (Brick& brk : brickGrid)
			{
				ball.CheckCollision(&brk);
			}

			ball.MoveOneStep(deltaTime);

			if (ball.y < -1.0f)
			{
				world.erase(world.begin() + i);
				continue;
			}

			ball.DrawCircle();
			++i;
		}

		paddle.drawBrick();

		for (Brick& b : brickGrid)
		{
			b.drawBrick();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}