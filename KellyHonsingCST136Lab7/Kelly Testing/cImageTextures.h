/*Kelly Honsinger
Date Created:10/18/2015
Last Modification Date:11/16/2015
Lab Number: 6
File Name: cImageTextures.h
-----------------------------------------------------------------------------

Class:cImageTextures
	Class that renders images to screen.  It renders in two ways.  From the automatic loop and the 
	controlled loop.  In the auto loop it displays the images in quick sucession across the screen
	in a way that prevents all gaps of the renderer showing.  In the controlled loop it lets the user
	scroll through the images using the arrow keys.
-----------------------------------------------------------------------------
Constructors:
cImageTextures();	default	constructor:
{
SDL_Renderer * imageRenderer;
SDL_Texture * imageTexture;
const int TIME = 2;
SDL_Rect * imageRect;
const int RENDERHEIGHT = 480;
const int RENDERWIDTH= 640;
}
cImageTextures(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer);  //Constructor
cImageTextures(cImageTextures & imgCpy);  //CopyConstructor

cImageTextures& operator=(cImageTextures & imgCPY);  //Assignment Operator

virtual ~cImageTextures();   //Destructor

------------------------------------------------------------------------------
Mutators: NONE

Methods:
virtual void Render();
	Virtual method that inherits from PVBC: cRender
------------------------------------------------------------------------------
*/

#ifndef CIMAGETEXTURES_H
#define CIMAGETEXTURES_H

#include <SDL.h>


const int TIME = 2;				//delay
const int RENDER_HEIGHT = 480;	//renderer height
const int RENDER_WIDTH = 640;	//renderer width

enum IMAGE_COUNT				//enum keeps track of the total amount of images
{
	IMAGE_FIRST,
	IMAGE_SECOND,
	IMAGE_THIRD,
	IMAGE_FOURTH,
	IMAGE_TOTAL
};

class cImageTextures  
{
public:
	//CONSTRUCTORS
	cImageTextures();
	cImageTextures(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer);	//constructor
	cImageTextures(const cImageTextures & imgCpy);								//copy constructor
	cImageTextures& operator=(cImageTextures & imgCPY);						//assignment operator
	//DESTRUCTOR
	virtual ~cImageTextures();												//virutal destructor
	//METHODS
	void Render(cImageTextures * image2);									//Render method displays images in automatic loop
	void CntrlLoopRender();													//Render method for images in controlled loop
	//mutators
	SDL_Renderer  *imgRendererGetter();
	SDL_Texture * imgTextureGetter();
	SDL_Rect * imgRectGetter();

private:
	SDL_Renderer * mImageRenderer;											//renderer
	SDL_Texture * mImageTexture;												//texture
	SDL_Rect * mImageRect;													//renderer cliping size
	
};
#endif
