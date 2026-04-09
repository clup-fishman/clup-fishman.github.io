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
// - ONOFF: Enum for brick visibility
// - paddle: Forward declaration for global paddle object
// - isPressed: Global debounce flag for input handling
//
// Author: Caleb Luplow
// Date: 3/26/2026
// Assignment: CS-499 Capstone - CS-330 Coding Collisions Enhancement
///////////////////////////////////////////////////////////////////////////////

#pragma once

// Convert degrees to radians
const float DEG2RAD = 3.14159 / 180;

// Brick HP values
const int BRICK_HP_RED = 3;
const int BRICK_HP_YELLOW = 2;
const int BRICK_HP_GREEN = 1;

// Brick color values
const float COLOR_GRAY[3] = { 0.3f, 0.3f, 0.3f };
const float COLOR_RED[3] = { 0.9f, 0.2f, 0.2f };
const float COLOR_YELLOW[3] = { 0.9f, 0.9f, 0.2f };
const float COLOR_GREEN[3] = { 0.2f, 0.9f, 0.2f };

// Brick states
enum BRICKTYPE { REFLECTIVE, DESTRUCTIBLE };
enum ONOFF { ON, OFF };

// Forward declaration of Paddle
class Paddle;
extern Paddle paddle;

// Global debounce flag for inputs
extern bool isPressed;
