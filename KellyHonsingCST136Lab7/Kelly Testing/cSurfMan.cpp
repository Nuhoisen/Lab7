//Kelly Honsinger
#include "cSurfMan.h"

/*.........................................................................................
cSurfMan()

Purpose:(class constructor.  Initialize the class' private data members.

Entry: None. Sets all to null.

Exit: None.
.........................................................................................
*/
cSurfMan::cSurfMan()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	for (int i = 0; i < PATH_TOTAL; i++)
	{
		mTexture[i] = nullptr;
	}
}

/*.........................................................................................
cSurfMan(cSurfMan & copy)

Purpose:(copy constructor.  Initialize the class' data members to the copy's.

Entry: cSurfMan & copy; copy to be passed

Exit: None.
.........................................................................................
*/
cSurfMan::cSurfMan(cSurfMan & copy)
{
	mRenderer= copy.mRenderer;
	mWindow= copy.mWindow;
	for (int i = 0; i < PATH_TOTAL; i++)
		mTexture[i]=copy.mTexture[i];
}

/*.........................................................................................
cSurfMan & operator=(cSurfMan & copy)

Purpose:(Assignment Operator.  Initialize the class' data members to the copy's when the equal sign is used.

Entry: cSurfMan & copy; copy to be passed

Exit: Invoking object
.........................................................................................
*/
cSurfMan & cSurfMan::operator=(cSurfMan & copy)
{
	mRenderer = copy.mRenderer;
	mWindow = copy.mWindow;
	for (int i = 0; i < PATH_TOTAL; i++)
		mTexture[i] = copy.mTexture[i];

	return *this;
}

/*.........................................................................................

~cSurfMan()

Purpose: Class Destructor.

Entry:None

Exit:None
..........................................................................................
*/
cSurfMan::~cSurfMan() 
{	
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	mWindow = nullptr;
	mRenderer = nullptr;

	for (int i = 0; i < PATH_TOTAL; i++)
	{
		SDL_DestroyTexture(mTexture[i]);
		mTexture[i] = nullptr;
	}
}

/*..........................................................................................
bool Init(string * files);

Purpose:Initializes the program by checking for the SDL Library files and then
constructing a window that will hold the image.

Entry: char * headerName[]: is a pointer to a char array.  It holds the command line
arguments, and in this case the image file's directory and name.

Exit: bool pass: is a variable that returns true if everything succeeds in the method.
...........................................................................................
*/
bool cSurfMan::Init(string * path)
{
	bool pass = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Initialization failure. ERROR: ", SDL_GetError();
		pass = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Linear Texture Filtering not enabled!";
		}	 
		mWindow = SDL_CreateWindow(path->c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == nullptr)
		{
			cout << "Can't Create Window! SDL ERROR: " << SDL_GetError();
			pass = false;
		}
		else
		{
			mRenderer = SDL_CreateRenderer(mWindow, -1,	SDL_RENDERER_ACCELERATED);
			if (mRenderer == nullptr)
			{
				cout << "Renderer Failed to be created!";
				pass = false;
			}
			else
			{	
				SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);  //(UNIT8 red, UNIT8 green, UNIT8 blue, UNIT8 Alpha) sets the renderer color to black
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_Image couldn't initialize!";
					pass = false;
				}
			}
		}
	}
	return pass;
}

/*
...........................................................................................

bool LoadMedia( string * path);

Purpose:Loads the appropriate Bmp file to correspond with the correct key. Uses an enum to
simplify the data.

Entry: Takes input from an pointer to enum array.

Exit: Returns a bool to check that all the files were opened properly
...........................................................................................
*/
bool cSurfMan::LoadMedia(string * path)
{
	int textureIndex = 0;
	bool success = true;
	for (int i = 1; i <= PATH_TOTAL; i++)
	{	
		mTexture[textureIndex] = LoadSurface(path[i]); //First image
		if (mTexture[textureIndex] == nullptr)//Checks that the image successfully opened
		{
			cout << "Failed to load image!\n";
			success = false;
		}
		textureIndex++;	//increment index
	}	
	
	return success; //true bool returns successful 
}

/*...........................................................................................
SDL_Texture * LoadSurface(string surfacePath);

Purpose: Function executed within LoadMedia function that takes the file directory and
assigns it to the right enum array path.

Entry: Takes the image directory in the form of a string.

Exit: Returns SDL_Texture pointer.
..........................................................................................
*/
SDL_Texture* cSurfMan::LoadSurface(std::string path)
{	
	SDL_Texture *tempTexture= nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());//Load image at specified path
	if (loadedSurface == nullptr)
	{
		cout << "Unable to load image, SDL Error: %s\n" << SDL_GetError();
	}
	else
	{	
		tempTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);//Convert surface to texture
		if (tempTexture == nullptr)
		{
			cout << "Unable to create texture from image! SDL Error:"
				<< SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface); //Get rid of old loaded surfaces
		loadedSurface = nullptr;
	}
	return tempTexture;
}

/*..........................................................................................
void Close();

Purpose: Clears the memory of all data that was initialized during the program run.

Entry: none

Exit: none
...........................................................................................
*/
void cSurfMan::Close()
{
	for (int i = 0; i < PATH_TOTAL; i++)
	{
		SDL_DestroyTexture(mTexture[i]);	//destroy texture
		mTexture[i] = nullptr;
	}
	
	SDL_DestroyRenderer(mRenderer); //destroy window and renderer
	mRenderer = nullptr;

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit(); 
}

/*...........................................................................................
SDL_Renderer * RendererGetter();

Purpose: Mutator: Getter that retrieves the window data member

Entry: None

Exit: Returns the window member
...........................................................................................
*/
SDL_Renderer * cSurfMan::RendererGetter()
{
	return mRenderer;		//returns the address of mRenderer
}

/*...........................................................................................
SDL_Texture * TextureGetter(int index);

Purpose: Mutator: Getter that retrieves the window data member

Entry: int index; index of texture needed

Exit: Returns the window member
...........................................................................................
*/
SDL_Texture * cSurfMan::TextureGetter(int index)
{
	return mTexture[index];		//returns the address of mTexture
}

