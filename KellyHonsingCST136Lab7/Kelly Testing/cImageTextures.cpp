//Kelly Honsinger
#include "cImageTextures.h"

/*
...................................................................
cImageTextures(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer)

Purpose:Class contructor; Initialize the class' private data members.

Entry: SDL_Texture * tempTexture :initializes object texture.
 SDL_Renderer * tempRenderer :initializes object renderer.

Exit: None
...................................................................*/
cImageTextures::cImageTextures(SDL_Texture * tempTexture, SDL_Renderer * tempRenderer)
{
	mImageTexture= tempTexture;
	mImageRenderer = tempRenderer;
	mImageRect = new SDL_Rect;
	mImageRect -> x = 0;
	mImageRect -> y = 0;
	mImageRect -> w = RENDER_WIDTH;
	mImageRect -> h = RENDER_HEIGHT;
}
cImageTextures::cImageTextures()
{
	mImageTexture = nullptr;
	mImageRenderer = nullptr;
	mImageRect = nullptr;
	
}
/*
...................................................................
cImageTextures(cImageTextures & imgCpy)

Purpose:copy contructor; Initialize the class' private data members.

Entry: cImageTextures & imgCpy

Exit: None
...................................................................*/
cImageTextures::cImageTextures(const cImageTextures & imgCpy)
{
	mImageTexture = imgCpy.mImageTexture;
	mImageRenderer = imgCpy.mImageRenderer;
	mImageRect = imgCpy.mImageRect;
}

/*
...................................................................
cImageTextures& operator=(cImageTextures& imgCPY)

Purpose:assignment operator; Initialize the class' private data members when equal sign is used.

Entry: cImageTextures& imgCPY; copy object to initialize to.

Exit: Invoking object
...................................................................*/
cImageTextures& cImageTextures::operator=(cImageTextures& imgCPY)
{
	mImageTexture = imgCPY.mImageTexture;
	mImageRenderer = imgCPY.mImageRenderer;
	mImageRect = imgCPY.mImageRect;

	return * this;
}

/*
...................................................................
~cImageTextures()

Purpose:destructor; Deletes all dynamically allocated memory and sets pointers to null.

Entry: None

Exit: None
...................................................................*/
cImageTextures::~cImageTextures()
{
	mImageTexture = nullptr;
	SDL_DestroyTexture(mImageTexture);
	mImageTexture = nullptr;
	SDL_DestroyRenderer(mImageRenderer);
	mImageRenderer = nullptr;
}

/*
...................................................................
void Render()

Purpose:Method that takes the two image textures and prints them to screen.

Entry: The invoking object passes an object of the following image so that they can both 
be rendered at the sametime on the same screen.

Exit: None
...................................................................*/
void cImageTextures::Render(cImageTextures * image2)
{
	SDL_Rect * tempRect = mImageRect;
	SDL_Rect * temp2Rect = mImageRect;													//its okay for the tempRects to be assigned to the same address because they just overwrite their x values with the new index
	for (int i = 0; i <RENDER_WIDTH ; i++)
	{
		(tempRect -> x) = i;
		SDL_RenderClear(mImageRenderer);
		SDL_RenderCopy(mImageRenderer, mImageTexture, nullptr, tempRect);					//SDL_RenderCopy(RENDERER, Texture your loading from, rectangle you're drawing from, rectangle you're drawing to)
		
		
		(temp2Rect->x) = (-RENDER_WIDTH + i);											//rect that has coordinants so that the right side of the texture renders first
		SDL_RenderCopy(mImageRenderer, image2->mImageTexture, nullptr, temp2Rect);		//renders following image using temp2Rects Coordinates 
		SDL_RenderPresent(mImageRenderer);												//both images get rendered at the same time
		SDL_Delay(TIME);
	}
}

/*
...................................................................
void CntrlLoopRender()

Purpose:Method that takes the image texture and renderer and prints them from the user controlled loop.

Entry: None

Exit: None
...................................................................*/
void cImageTextures::CntrlLoopRender()
{	
		SDL_RenderClear(mImageRenderer);
		SDL_RenderCopy(mImageRenderer, mImageTexture, nullptr, nullptr);					//SDL_RenderCopy(RENDERER, Texture your loading from, rectangle you're drawing from, rectangle you're drawing to)
		SDL_RenderPresent(mImageRenderer);
		SDL_Delay(TIME);
}




SDL_Renderer * cImageTextures::imgRendererGetter()
{
	return mImageRenderer;		//returns the address of mRenderer
}


SDL_Texture * cImageTextures::imgTextureGetter()
{
	return mImageTexture;		//returns the address of mTexture
}

SDL_Rect  *cImageTextures::imgRectGetter()
{
	return  mImageRect;
}