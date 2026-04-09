///////////////////////////////////////////////////////////////////////////////
// Utilities.h
// ===========
// This header file declares support functions for handling user input,
// scene setup, and grid generation. These functions configure the
// OpenGL viewport, manage game initialization, and react to player input.
//
// Key Features:
// -------------
// - Process keyboard input for spawning balls and moving the paddle
// - Set up the orthographic projection for proper window scaling
// - Generate a structured grid of bricks for the playing area
//
// Author: Caleb Luplow
// Date: 6/24/2025
// Assignment: 8-2 Assignment - CS-330 Computational Graphics and Visualization
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GLFW\glfw3.h>
#include <vector>
#include <GameObjects.h>
#include "constants.h"


using namespace std;

// Checks for input for keypresses
void ProcessInput(GLFWwindow* window, float deltaTime);

// Sets up a projection for the game screen
void SetupScene(int width, int height);

// Generates a grid of bricks for the game field
void GenerateBrickGrid(vector<Brick>& bricks, int rows, int cols, float bWidth,
	float bHeight, float spaceX, float spaceY);
