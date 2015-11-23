/*Kelly Honsinger
Date Created:10/18/2015
Last Modification Date 11/16/2015
Lab Number: 6
File Name: cCollisionObj.h

-----------------------------------------------------------------------------
Class:cCollisionObj

Class that is implemented in order to render collisions.  It acts as a start screen in this game and
iniates the image loop once the user has the dot collide into the image.

----------------------------------------------------------------------------
Constructors:

cCollisionObj(SDL_Texture *tempTexture, SDL_Renderer * tempRenderer);
cCollisionObj();														//Default constructor
cCollisionObj(cCollisionObj &copy);										//Copy constructor
cCollisionObj & operator=(cCollisionObj &copy);							//Assignment Operator
virtual ~cCollisionObj();												//virtual destructor

-----------------------------------------------------------------------------
Mutators: NONE

-----------------------------------------------------------------------------
Methods:

void Start(SDL_Texture* button): Start method initiates collision screen.
void HandleEvent(SDL_Event& collideEvent): includes a SDL_Event object that runs the collision screen loop.
bool CheckCollision() : Checks if the rendered dot is colliding with either the sides of the renderer or the 
rendered image in the center of it. 
void RenderColliders(SDL_Texture* renderButton):  method renders the dot on screen as well as the image it collides into
bool Move(): move method causes the dot object to inch forward on the screen.

-----------------------------------------------------------------------------
*/

#ifndef cCOLLISIONOBJ_H
#define cCOLLISIONOBJ_H

#include <SDL.h>

const int DOT_VELOCITY=5;				//dot velocity in pixels per keyhold
const int DOT_WIDTH = 20;				//dot width dimension
const int DOT_HEIGHT = 20;				//dot height dimension
const int SCREEN_WIDTH = 640;			//Screen width dimension
const int SCREEN_HEIGHT = 480;			//Screen height dimension
const int START_BUTTON_WIDTH = 145;		//Start button width(pixels)
const int START_BUTTON_HEIGHT = 130;	//Start button height(pixels)

class cCollisionObj
{
public:
	//CONSTRUCTORS
	cCollisionObj(SDL_Texture *tempTexture, SDL_Renderer * tempRenderer);	//Constructor is passed  texture and renderer										
	cCollisionObj();														//Default constructor
	cCollisionObj(cCollisionObj &copy);										//Copy constructor
	cCollisionObj & operator=(cCollisionObj &copy);							//Assignment Operator
	virtual ~cCollisionObj();												//destructor
	//METHODS
	void Start(SDL_Texture* button);										//Start game method
	void HandleEvent(SDL_Event& collideEvent);								//HandleEvent method
	bool Move();															//move method
	void RenderColliders(SDL_Texture* renderButton);						//Render method
	bool CheckCollision();													//Method that checks if dot hit anything	

private:
	SDL_Texture * mDotTexture;												//Texture that holds dot
	SDL_Renderer * mCollisionRenderer;										//Renderer 
	SDL_Rect  mDotDimensions;												//dot dimensions
	SDL_Rect  mRectCoordinates;												//Rectangle dimensions and coordinates
	int mDotVelX, mDotVelY;													//Incremental velocity counters
	int mDotPosX, mDotPosY;													//position trackers that pass info to SDL Rects
};
#endif