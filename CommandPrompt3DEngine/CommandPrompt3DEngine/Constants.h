#ifndef CONSTANTS_H
#define CONSTANTS_H

// Mathematical constants
constexpr float fPi = 3.14159f;

// Renderer constants
extern const int nScreenWidth;	// Terminal Char resolution
extern const int nScreenHeight; // Terminal Char resolution
extern const float fFOV;		// Field of view (radians)
extern const float fDepth; 		// Maximum rendering distance

// Player constants
extern const float fPlayerX;	
extern const float fPlayerY;
extern const float fPlayerA;			// Player angle (radians)
extern const float fPlayerSensitivity;
extern const float fPlayerSpeed;

// Player movement keys
extern const char cForward;		
extern const char cBackward;	
extern const char cLeft;
extern const char cRight;
extern const char cRotateLeft;
extern const char cRotateRight;

// Map constants
extern const int nMapHeight; 
extern const int nMapWidth;

#endif // CONSTANTS_H
