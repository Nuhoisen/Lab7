//Kelly Honsinger
#include "cCollisionObj.h"


/*
...................................................................
cCollisionObj(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer )

Purpose: Class contructor; Initialize the class' private data members.


Entry: SDL_Texture * tempTexture: Texture taken from surfman class
, SDL_Renderer * tempRenderer:Renderer taken from surfman class

Exit: None
...................................................................*/
cCollisionObj::cCollisionObj(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer )
{
	mDotTexture = tempTexture;
	mCollisionRenderer = tempRenderer;
	
	mDotPosX = 0;						//dot starts at position (0,0)
	mDotPosY = 0;

	mDotVelX = 0;
	mDotVelY = 0;
	
	mDotDimensions.h = DOT_HEIGHT;		//set sdl rect dimensions to dot height and width
	mDotDimensions.w = DOT_WIDTH;
	
	mRectCoordinates.x = SCREEN_WIDTH / 2;//place the top left side of the image onto the center of the screen
	mRectCoordinates.y = SCREEN_WIDTH / 2;
	mRectCoordinates.h = START_BUTTON_HEIGHT;
	mRectCoordinates.w = START_BUTTON_WIDTH;
}

/*
...................................................................
cCollisionObj()

Purpose:contructor; Initialize the class' private data members.

Entry : None

Exit : None
...................................................................*/
cCollisionObj::cCollisionObj()
{
	mDotTexture = nullptr;
	mCollisionRenderer = nullptr;

	mDotPosX = 0;
	mDotPosY = 0;

	mDotVelX = 0;
	mDotVelY = 0;

	mDotDimensions.h = DOT_HEIGHT;			
	mDotDimensions.w = DOT_WIDTH;

	mRectCoordinates.x = SCREEN_WIDTH / 2;			
	mRectCoordinates.y = SCREEN_WIDTH / 2;
	mRectCoordinates.h = START_BUTTON_HEIGHT;
	mRectCoordinates.w = START_BUTTON_WIDTH;
}

/*
...................................................................
cCollisionObj(cCollisionObj & copy)

Purpose:Copy contructor; Initialize the class' private data members to the passed copy.

Entry : cCollisionObj & copy

Exit : None
...................................................................*/
cCollisionObj::cCollisionObj(cCollisionObj & copy)
{
	mDotTexture = copy.mDotTexture;;
	mCollisionRenderer = copy.mCollisionRenderer;

	mDotPosX = copy.mDotPosX;
	mDotPosY = copy.mDotPosY;

	mDotVelX = copy.mDotVelX;
	mDotVelY = copy.mDotVelY;

	mDotDimensions.h = DOT_HEIGHT;
	mDotDimensions.w = DOT_WIDTH;

	mRectCoordinates.x = SCREEN_WIDTH / 2;
	mRectCoordinates.y = SCREEN_WIDTH / 2;
	mRectCoordinates.h = START_BUTTON_HEIGHT;
	mRectCoordinates.w = START_BUTTON_WIDTH;
}

/*
...................................................................
cCollisionObj & operator=(cCollisionObj & copy)

Purpose:assignment contructor; Initialize the class' private data members to the passed copy.

Entry :cCollisionObj & copy; copy object to initialize to.

Exit : invoked object
...................................................................*/
cCollisionObj & cCollisionObj::operator=(cCollisionObj & copy)
{
	mDotTexture = copy.mDotTexture;;
	mCollisionRenderer = copy.mCollisionRenderer;

	mDotPosX = copy.mDotPosX;
	mDotPosY = copy.mDotPosY;

	mDotVelX = copy.mDotVelX;
	mDotVelY = copy.mDotVelY;

	mDotDimensions.h = DOT_HEIGHT;
	mDotDimensions.w = DOT_WIDTH;

	mRectCoordinates.x = SCREEN_WIDTH / 2;
	mRectCoordinates.y = SCREEN_WIDTH / 2;
	mRectCoordinates.h = START_BUTTON_HEIGHT;
	mRectCoordinates.w = START_BUTTON_WIDTH;
	
	return *this;
}

/*
...................................................................
~cCollisionObj()

Purpose:destructor; Deletes all dynamically allocated memory and sets pointers to null.

Entry : None

Exit : None
...................................................................*/
cCollisionObj::~cCollisionObj()
{
	SDL_DestroyRenderer(mCollisionRenderer);
	mCollisionRenderer = nullptr;
	SDL_DestroyTexture(mDotTexture);
	mDotTexture=nullptr;
	mRectCoordinates.h = 0;
	mRectCoordinates.w = 0;
	mRectCoordinates.x = 0;
	mRectCoordinates.y = 0;
	
	mDotDimensions.h = 0;
	mDotDimensions.w = 0;
	mDotDimensions.x = 0;
	mDotDimensions.y = 0;
}

/*
...................................................................
void Start(SDL_Texture* button)

Purpose:Iniates Game; Calls all methods including sdl event loop.  Exits when user x's out or collides
dot into the image.

Entry : SDL_Texture* button: texture that will be rendered as the button on screen.

Exit : None
...................................................................*/
void cCollisionObj::Start(SDL_Texture* button)
{
	SDL_Event collisionEvent;
	bool quit = false;
	bool collide = false;

	while (!quit && !collide)						//quit if the user exits or the dot hits the side of the iamge
	{
		while (SDL_PollEvent(&collisionEvent) != 0)
		{
			if (collisionEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			this->HandleEvent(collisionEvent);
			collide= this->Move();	
		}
		this->RenderColliders(button);
	}
}

/*
...................................................................
void HandleEvent(SDL_Event& collideEvent)

Purpose:Reads key input and adjusts dot velocity accordingly

Entry : SDL_Event& collideEvent: SDL_Event contains data acquired from the user hitting keys on the keyboard

Exit : None
...................................................................*/
void cCollisionObj::HandleEvent(SDL_Event& collideEvent)
{
	if (collideEvent.type == SDL_KEYDOWN && collideEvent.key.repeat == 0)	//by default the keys are active when pressed
		//so in order to have the image move around while the keys are held down a repeat check must be done.
	{
		switch (collideEvent.key.keysym.sym)
		{
		case SDLK_UP: 
			mDotVelY -= DOT_VELOCITY;			//dot velocity increases by 10 if respective key is pressed
			break;
		case SDLK_DOWN:
			mDotVelY += DOT_VELOCITY;
			break;
		case SDLK_LEFT: 
			mDotVelX -= DOT_VELOCITY; 
			break;
		case SDLK_RIGHT:
			mDotVelX += DOT_VELOCITY; 
			break;
		}
	}
	else if (collideEvent.type == SDL_KEYUP && collideEvent.key.repeat == 0)	//Check when the key is released
	{
		switch (collideEvent.key.keysym.sym)
		{
		case SDLK_UP:
			mDotVelY += DOT_VELOCITY;			//offset the velocity so that the dot stops moving
			break;
		case SDLK_DOWN:
			mDotVelY -= DOT_VELOCITY;
			break;
		case SDLK_LEFT: 
			mDotVelX += DOT_VELOCITY;
			break;
		case SDLK_RIGHT: 
			mDotVelX -= DOT_VELOCITY; 
			break;
		}
	}
}

/*
...................................................................
bool Move()

Purpose:Assigns velocity to dot dimensions which moves the dot; also checks if the dot has collided
anywhere.  If it has, it will either start the game in the case of hitting the image, or simply stop the 
dot from exiting the renderer otherwise.

Entry : None

Exit : bool is used to check if the the dot hit the image inside.
...................................................................*/
bool cCollisionObj::Move()
{

	mDotPosX += mDotVelX;
	mDotDimensions.x = mDotPosX;

	if ((mDotPosX < 0) || (mDotPosX + DOT_WIDTH > SCREEN_WIDTH) || CheckCollision())	//checks if the dot is colliding on x axis of the renderer
		//or if it is colliding into the image
	{
		if (CheckCollision())
		{
			mDotPosX -= mDotVelX;	//if checkcollision() returns true, it means the dot hit the x axis of the image
			//and its time to exit the loop
			mDotDimensions.x = mDotPosX;
			return true;
		}
		else
		{
			mDotPosX -= mDotVelX;	//otherwise just stop the dot from moving
			mDotDimensions.x = mDotPosX;
			return false;
		}
	}
	mDotPosY += mDotVelY;
	mDotDimensions.y = mDotPosY;

	if ((mDotPosY < 0) || (mDotPosY + DOT_HEIGHT > SCREEN_HEIGHT) || CheckCollision()) //checks if the dot is exceeding the y axis boundary
		//or if it is collding into the image
	{
		if (CheckCollision())
		{
			mDotPosY -= mDotVelY;	//if checkcollision() returns true, it means the dot hit the y axis of the image
			//and its time to exit the loop
			mDotDimensions.y = mDotPosY;
			return true;
		}
		else
		{
			mDotPosY -= mDotVelY;	//otherwise just stop the dot from moving
			mDotDimensions.y = mDotPosY;
			return false;
		}
	}
}

/*
...................................................................
bool CheckCollision()

Purpose: checks if the dot hit image by looking at the dot placement in respect
to its dimensions and the images dimensions.

Entry : None

Exit : bool is used to check if the the dot hit the image inside.
...................................................................*/
bool cCollisionObj::CheckCollision()
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;


	leftA = mDotDimensions.x;	//assign the dimensions and position of the dot to "A"
	rightA = mDotDimensions.x + mDotDimensions.w;
	topA = mDotDimensions.y;
	bottomA = mDotDimensions.y + mDotDimensions.h;


	leftB = mRectCoordinates.x;	//assign the dimensions and position of the image to "B"
	rightB = mRectCoordinates.x + mRectCoordinates.w;
	topB = mRectCoordinates.y;
	bottomB = mRectCoordinates.y + mRectCoordinates.h;

	if (bottomA <= topB)		//if the bot dot position is not within the top image position then return false
	{
		return false;
	}

	if (topA >= bottomB)		//if the top dot position is not within the bot image position then return false
	{
		return false;
	}

	if (rightA <= leftB)	//if the right side of the dot is not within the left side of the image then return false
	{
		return false;
	}

	if (leftA >= rightB)	//if the left side of the dot is not within the right side of the image then return false
	{
		return false;
	}

	return true;				//otherwise the dot has hit the side of the image and the collision method returns true
}

/*
...................................................................
void RenderColliders(SDL_Texture* renderButton)

Purpose: Renders both the dot and the image to the screen

Entry : SDL_Texture * renderButton: is texture used to represent the 
image in the renderer

Exit : None
...................................................................*/
void cCollisionObj::RenderColliders(SDL_Texture* renderButton)
{
	SDL_SetRenderDrawColor(mCollisionRenderer, 0xFF, 0xFF, 0xFF, 0xFF);				//(Renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a ):sets the renderer to white
	SDL_RenderClear(mCollisionRenderer);											//clears all previous textures
	SDL_RenderCopy(mCollisionRenderer, renderButton, nullptr, &mRectCoordinates);	//copys the SDL_Rect renderbutton's dimensions to mRectCoordinates coordinates
	
	SDL_Rect renderQuad = { mDotPosX, mDotPosY, DOT_WIDTH, DOT_WIDTH };				

	SDL_RenderCopy(mCollisionRenderer, mDotTexture, nullptr, &renderQuad);			//Renders dot dimensions at renderQuad coordinates which puts it at the top left of the renderer
	SDL_RenderPresent(mCollisionRenderer);	//presents the image.
}

