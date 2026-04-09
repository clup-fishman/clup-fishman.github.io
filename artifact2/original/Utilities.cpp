///////////////////////////////////////////////////////////////////////////////
// Utilities.cpp
// ===========
// This file implements utility functions used in the game. This includes
// real-time input handling, setting up the OpenGL projection to maintain
// consistent aspect ratios, and generating a dynamic grid of bricks that
// vary by row and type.
//
// Functions Implemented:
// -------------
// - ProcessInput: Handles player controls
// - SetupScene: Configures the projection matrix based on window size
// - GenerateBrickGrid: Dynamically places bricks into a grid with color/state logic
//
// Author: Caleb Luplow
// Date: 6/24/2025
// Assignment: 8-2 Assignment - CS-330 Computational Graphics and Visualization
///////////////////////////////////////////////////////////////////////////////

#include "Utilities.h"

// External reference for the world vector
extern vector<Circle> world;

/**
*  Processes user input and performs actions based on key presses.
*  - ESC closes the window.
*  - SPACE spawns a new ball (one per press).
*  - LEFT/RIGHT moves the paddle.
* 
* @param window The GLFW window to check for input.
* @param deltaTime Time since last frame, used for consistent movement speed.
*/
void ProcessInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!isPressed)
		{
			double r, g, b;

			// Changed logic to ensure no black balls are created
			do
			{
				r = (rand() % 1001) / 1000.0f;
				g = (rand() % 1001) / 1000.0f;
				b = (rand() % 1001) / 1000.0f;
			} while (r < 0.05f && g < 0.05f && b < 0.05f);

			Circle B(0, 0, 0.025, r, g, b);
			world.push_back(B);
			isPressed = true; // Debounce flag ensures only one ball is spawned per keypress
		}
	}
	else
	{
		isPressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		paddle.moveLeft(deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		paddle.moveRight(deltaTime);
	}
}

/**
*  Configures the OpenGL projection matrix to maintain the aspect ratio
*  of the scene when the window size changes.
* 
*  @param width The width of the rendering window.
*  @param height The height of the rendering window.
*/
void SetupScene(int width, int height)
{
	float ratio = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ratio >= 1.0f)
	{
		glOrtho(-ratio, ratio, -1.0, 1.0, -1.0, 1.0);
	}
	else
	{
		glOrtho(-1.0, 1.0, -1.0f / ratio, 1.0f / ratio, -1.0, 1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/**
*  Creates a grid of bricks with defined type, size, and spacing.
*  Bricks are arranged in rows and columns starting from a fixed origin point.
*  Some bricks require multiple hits and change colors when damaged.
* 
*  @param bricks The address of the array of bricks to store.
*  @param rows The number of rows in the brick grid.
*  @param cols The number of columns in the brick grid.
*  @param bWidth The width of a brick object.
*  @param bHeight The height of a brick object.
*  @param spaceX The x-value space between bricks.
*  @param spaceY The y-value space between bricks.
*/
void GenerateBrickGrid(vector<Brick>& bricks, int rows, int cols, float bWidth,
	float bHeight, float spaceX, float spaceY)
{
	// Track brick types to prevent cutting off destructable bricks
	vector<vector<BRICKTYPE>> brickTypeGrid(rows, vector<BRICKTYPE>(cols, DESTRUCTIBLE));

	// Calculate grid size
	float totalWidth = cols * bWidth + (cols - 1) * spaceX;

	// Start from the top left corner
	float startX = -totalWidth / 2.0f;
	float startY = 0.9f;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			float x = startX + col * (bWidth + spaceX) + bWidth / 2;
			float y = startY - row * (bHeight + spaceY) - bHeight / 2;

			// Decide on a gray indestructible brick
			bool wantGray = (rand() / static_cast<float>(RAND_MAX) < 0.2f);

			// At least one brick must be breakable
			bool leftIsWall = (col > 0) && (brickTypeGrid[row][col - 1] == REFLECTIVE);
			bool topIsWall = (row > 0) && (brickTypeGrid[row - 1][col] == REFLECTIVE);

			// Ensures breakable blocks are not blocked
			if (wantGray && leftIsWall && topIsWall)
			{
				wantGray = false;
			}

			if (wantGray)
			{
				bricks.emplace_back(REFLECTIVE, x, y, bWidth, bHeight, 0.3f, 0.3f, 0.3f, 0);
				brickTypeGrid[row][col] = REFLECTIVE;
				continue;
			}

			// First two rows are red bricks
			if (row < 2)
			{
				bricks.emplace_back(REFLECTIVE, x, y, bWidth, bHeight,
					COLOR_RED[0], COLOR_RED[1], COLOR_RED[2], BRICK_HP_RED);
				brickTypeGrid[row][col] = REFLECTIVE;
			}
			// Next two rows are yellow bricks
			else if (row < 4)
			{
				bricks.emplace_back(REFLECTIVE, x, y, bWidth, bHeight,
					COLOR_YELLOW[0], COLOR_YELLOW[1], COLOR_YELLOW[2], BRICK_HP_YELLOW);
				brickTypeGrid[row][col] = REFLECTIVE;
			}
			// Rest of bricks are green
			else
			{
				bricks.emplace_back(DESTRUCTIBLE, x, y, bWidth, bHeight,
					COLOR_GREEN[0], COLOR_GREEN[1], COLOR_GREEN[2], BRICK_HP_GREEN);
				brickTypeGrid[row][col] = DESTRUCTIBLE;
			}
		}
	}
}