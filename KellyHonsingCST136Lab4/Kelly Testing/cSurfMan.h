/*Kelly Honsinger
Date Created:10/18/2015
Last Modification Date: 11/16/2015
Lab Number: 6
File Name: cGameLoop.h
-----------------------------------------------------------------------------

Class:cSurfMan
	This class is used to iniated the sdl libraries and load the images from the directory.
	It also acts as a composite object for cGameLoop.
.........................................................................................
CONSTRUCTOR & DESTRUCTOR
.........................................................................................
cSurfMan()

Purpose:(class constructor.  Initialize the class' private data members.

Entry: None. Sets all to null.

Exit: None.
.........................................................................................

Constructors:
cSurfMan(cSurfMan &copy);				Copy constructor
cSurfMan & operator=(cSurfMan &copy);	Assignment Operator
-----------------------------------------------------------------------------------------

~cSurfMan()

Purpose: Class Destructor.

Entry:None

Exit:None
..........................................................................................
METHODS
..........................................................................................
bool Init(string * files);

Purpose:Initializes the program by checking for the SDL Library files and then
constructing a window that will hold the image.

Entry: char * headerName[]: is a pointer to a char array.  It holds the command line
arguments, and in this case the image file's directory and name.

Exit: bool pass: is a variable that returns true if everything succeeds in the method.
...........................................................................................

bool LoadMedia(string * path);

Purpose:Loads the appropriate Bmp file to correspond with the correct key. Uses an enum to 
simplify the data.

Entry: Takes input from an pointer to enum array.

Exit: Returns a bool to check that all the files were opened properly
...........................................................................................

SDL_Texture * LoadSurface(string surfacePath);

Purpose: Function executed within LoadMedia function that takes the file directory and
assigns it to the right enum array path.

Entry: Takes the image directory in the form of a string.

Exit: Returns SDL_Texture pointer.
..........................................................................................
void Close();

Purpose: Clears the memory of all data that was initialized during the program run.

Entry: none

Exit: none
...........................................................................................
MUTATORS:
...........................................................................................
SDL_Renderer * RendererGetter();

Purpose: Getter that retrieves the window data member

Entry: None

Exit: Returns the window member
...........................................................................................
SDL_Texture * TextureGetter(int i);

Purpose: Getter that retrieves the window data member

Entry: int index; index of texture needed

Exit: Returns the window member
...........................................................................................
*/

#ifndef CSURFMAN_H
#define CSURFMAN_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using std::cout;
using std::cin;
using std::string;

const int WIDTH = 640;		//Renderer Width
const int HEIGHT = 480;		//Renderer Height

enum PATH_COUNT	//ENUM keeps count of image paths
{
	PATH_DEFAULT,
	PATH_FIRST,
	PATH_SECOND,
	PATH_THIRD,
	PATH_FOURTH,
	PATH_FIFTH,
	PATH_TOTAL
};

class cSurfMan 
{
public:
	//CONSTRUCTORS
	cSurfMan();								//constructor
	cSurfMan(cSurfMan & copy);				//copy constructor
	cSurfMan & operator=(cSurfMan & copy);	//assignment operator
	virtual ~cSurfMan();					//destructor
	//METHODS
	bool Init(string * files);				//initializes
	bool LoadMedia( string * path);			//loads media
	SDL_Texture * LoadSurface(string surfacePath);//loads path surface
	void Close();							//gets rid of SDL window, renderer, and textures.
	//MUTATORS
	SDL_Renderer * RendererGetter();		//returns renderer
	SDL_Texture * TextureGetter(int index);	//returns texture

private:
	SDL_Window * mWindow;					//WINDOW
	SDL_Renderer * mRenderer;				//RENDERER
	SDL_Texture * mTexture[PATH_TOTAL];		//array of textures
};
#endif 