///////////////////////////////////////////////////////////////////////////////
// constants.h
// ===========
// This file defines global constants, enums, and forward declarations used
// in the game. This includes color values, hit point levels, brick types,
// and global flags that control game behavior.
//
// Definitions:
// -------------
// - DEG2RADL: Conversion from degrees to radians
// - BRICK_HP_*: Hit point values for various colored bricks
// - COLOR_*: RGB values for each brick type
// - BRICKTYPE: Enum for brick types
// - ONOFF: Enum for brick visability
// - paddle: Forward declaration for global paddle object
// - isPressed: Global debounce flag for input handling
//
// Author: Caleb Luplow
// Date: 6/24/2025
// Assignment: 8-2 Assignment - CS-330 Computational Graphics and Visualization
///////////////////////////////////////////////////////////////////////////////

#pragma once

// Convert degrees to radians
const float DEG2RAD = 3.14159 / 180;

// Brick HP values
const float BRICK_HP_RED = 3;
const float BRICK_HP_YELLOW = 2;
const float BRICK_HP_GREEN = 1;

// Brick color values
const float COLOR_RED[3] = { 0.9f, 0.3f, 0.3f };
const float COLOR_YELLOW[3] = { 0.9f, 0.9f, 0.3f };
const float COLOR_GREEN[3] = { 0.3f, 0.9f, 0.3f };

// Brick states
enum BRICKTYPE { REFLECTIVE, DESTRUCTIBLE };
enum ONOFF { ON, OFF };

// Forward declaration of Paddle
class Paddle;
extern Paddle paddle;

// Global debounce flag for inputs
extern bool isPressed;
