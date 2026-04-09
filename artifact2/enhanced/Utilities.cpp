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
// - GenerateBrickGrid: Generates a structured brick grid with randomized wall placement
//
// Author: Caleb Luplow
// Date: 3/26/2026
// Assignment: CS-499 Capstone - CS-330 Coding Collisions Enhancement
///////////////////////////////////////////////////////////////////////////////

#include "Utilities.h"


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
* Brick Grid Generation Helper Functions
* --------------------------------------
* These static helper functions support the multi-stage brick generation
* algorithm by building the layout, applying placement rules, and converting
* the finalized layout into Brick objects.
*/

// Determines whether a gray wall brick should be placed at a given position.
// Prevents long horizontal runs and avoids blocking playable paths.
static bool ShouldPlaceGrayWall(
	const vector<vector<BrickLayoutType>>& layout,
	int row,
	int col,
	float grayChance,
	int consecutiveGrayCount,
	int maxGrayRun)
{
	bool wantGray = (rand() / static_cast<float>(RAND_MAX) < grayChance);

	if (!wantGray)
	{
		return false;
	}

	// Prevent long horizontal runs of gray bricks
	if (consecutiveGrayCount >= maxGrayRun)
	{
		return false;
	}

	// Prevent boxing in a playable brick from top and left
	bool leftIsWall = (col > 0) && (layout[row][col - 1] == WALL_GRAY);
	bool topIsWall = (row > 0) && (layout[row - 1][col] == WALL_GRAY);

	if (leftIsWall && topIsWall)
	{
		return false;
	}

	return true;
}


// Returns the base brick type for a row to create difficulty progression.
// Top rows are red, middle are yellow, and bottom are green.
static BrickLayoutType GetBaseTypeForRow(int row)
{
	if (row < 2)
	{
		return BRICK_RED;
	}
	else if (row < 4)
	{
		return BRICK_YELLOW;
	}

	return BRICK_GREEN;
}


// Builds the initial layout grid using controlled randomness and placement rules.
static void BuildLayoutGrid(
	vector<vector<BrickLayoutType>>& layout,
	int rows,
	int cols)
{
	// Tunable parameters controlling wall frequency and clustering.
	// Adjusting these values changes level difficulty and randomness.
	const float grayChance = 0.2f;
	const int maxGrayRun = 2;

	for (int row = 0; row < rows; ++row)
	{
		int grayRunCount = 0;

		for (int col = 0; col < cols; ++col)
		{
			BrickLayoutType baseType = GetBaseTypeForRow(row);

			if (ShouldPlaceGrayWall(layout, row, col, grayChance, grayRunCount, maxGrayRun))
			{
				layout[row][col] = WALL_GRAY;
				++grayRunCount;
			}
			else
			{
				layout[row][col] = baseType;
				grayRunCount = 0;
			}
		}
	}
}


// Ensures the bottom row contains at least one easily breakable brick.
// Prevents unfair or overly restrictive starting layouts.
static void EnsureBottomHasBreakables(
	vector<vector<BrickLayoutType>>& layout,
	int rows,
	int cols)
{
	int bottomRow = rows - 1;
	bool hasGreenBrick = false;

	for (int col = 0; col < cols; ++col)
	{
		if (layout[bottomRow][col] == BRICK_GREEN)
		{
			hasGreenBrick = true;
			break;
		}
	}

	// Guarantee at least one green brick on the bottom row
	if (!hasGreenBrick && cols > 0)
	{
		layout[bottomRow][cols / 2] = BRICK_GREEN;
	}
}


// Converts the layout grid into actual Brick objects with positions and colors.
static void CreateBricksFromLayout(
	vector<Brick>& bricks,
	const vector<vector<BrickLayoutType>>& layout,
	int rows,
	int cols,
	float bWidth,
	float bHeight,
	float spaceX,
	float spaceY)
{
	float totalWidth = cols * bWidth + (cols - 1) * spaceX;
	float startX = -totalWidth / 2.0f;
	float startY = 0.9f;

	bricks.clear();
	bricks.reserve(rows * cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			float x = startX + col * (bWidth + spaceX) + bWidth / 2.0f;
			float y = startY - row * (bHeight + spaceY) - bHeight / 2.0f;

			switch (layout[row][col])
			{
			case WALL_GRAY:
				bricks.emplace_back(
					REFLECTIVE, x, y, bWidth, bHeight,
					COLOR_GRAY[0], COLOR_GRAY[1], COLOR_GRAY[2], 0);
				break;

			case BRICK_RED:
				bricks.emplace_back(
					REFLECTIVE, x, y, bWidth, bHeight,
					COLOR_RED[0], COLOR_RED[1], COLOR_RED[2], BRICK_HP_RED);
				break;

			case BRICK_YELLOW:
				bricks.emplace_back(
					REFLECTIVE, x, y, bWidth, bHeight,
					COLOR_YELLOW[0], COLOR_YELLOW[1], COLOR_YELLOW[2], BRICK_HP_YELLOW);
				break;

			case BRICK_GREEN:
				bricks.emplace_back(
					DESTRUCTIBLE, x, y, bWidth, bHeight,
					COLOR_GREEN[0], COLOR_GREEN[1], COLOR_GREEN[2], BRICK_HP_GREEN);
				break;
			}
		}
	}
}

/**
* Generates a grid of bricks with structured randomness and gameplay constraints.
*
* The algorithm uses a multi-stage approach:
* 1. Build a layout grid representing brick types.
* 2. Apply validation rules to ensure fairness and playability.
* 3. Convert the layout into Brick objects for rendering.
* 
* @param bricks Output vector storing generated brick objects.
* @param rows Number of rows in the grid.
* @param cols Number of columns in the grid.
* @param bWidth Width of each brick.
* @param bHeight Height of each brick.
* @param spaceX Horizontal spacing between bricks.
* @param spaceY Vertical spacing between bricks.
*/
void GenerateBrickGrid(vector<Brick>& bricks, int rows, int cols, float bWidth,
	float bHeight, float spaceX, float spaceY)
{
	// Guard clause to prevent invalid grid generation
	if (rows <= 0 || cols <= 0)
	{
		bricks.clear();
		return;
	}

	vector<vector<BrickLayoutType>> layout(rows, vector<BrickLayoutType>(cols, BRICK_GREEN));

	BuildLayoutGrid(layout, rows, cols);
	EnsureBottomHasBreakables(layout, rows, cols);
	CreateBricksFromLayout(bricks, layout, rows, cols, bWidth, bHeight, spaceX, spaceY);
}
