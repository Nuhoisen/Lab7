/*Kelly Honsinger
Date Created:10/18/2015
Last Modification Date: 11/16/2015
Lab Number: 6
File Name: cGameLoop.h
-----------------------------------------------------------------------------

Class:cMainGame
	This Class is the class that iniates the game loop from the main.  It's method: BeginGame is called to start
	the game. It is the class that contains the aggregates and the composites.  Surfman object is the composite
	and CollisionObj and ImageTexture objects are the aggregates.
-----------------------------------------------------------------------------
Constructors: 
	cGameLoop();	default	constructor:
		{
		string * files;
		cRender * renderObject[IMAGE_TOTAL];
		cImageTextures * image;
		cspriteTextures * sprite;
		int index;
		ALL INITIALIZED TO NULL.
		}
	cGameLoop(char *argv[], int argc);		Constructor takes command line arguments
	virtual ~cGameLoop();					virtual destructor
	cGameLoop(cGameLoop &copy);				Copy constructor
	cGameLoop & operator=(cGameLoop &copy);	Assignment Operator

------------------------------------------------------------------------------
Mutators: NONE

Methods:
	void BeginGame();						
		This method iniates the game.
	
	void AutoGameLoop();
		This method iniates the first game loop which is the automatic display of images
	
	void ControlledGameLoop();
		This method iniates the games second loop which is user controlled.
	
	bool Retry();
		This method asks the user if they want to go again
------------------------------------------------------------------------------
*/

#ifndef CMAINGAME_H
#define CMAINGAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "cSurfMan.h"
#include "cImageTextures.h"


using std::cout;
using std::cin;
using std::vector;

class cGameLoop:  public cSurfMan
{
public: 
	//CONSTRUCTORS
	cGameLoop();							//Constructor Declaration
	cGameLoop(char *argv[], int argc);		//explicitly defined constructor
	~cGameLoop();							//Destructor Declaration
	cGameLoop(cGameLoop &copy);				//copy constructor
	cGameLoop & operator=(cGameLoop &copy);	//Assignment Operator
	//METHODS
	void BeginGame();						//iniates game
	void ControlledGameLoop();				//loop that the user controls
	void Render( cImageTextures renderTxt1,  cImageTextures renderTxt2);
	bool Retry();							//method that prompts the user to go again

private:
	string * mFiles;							//string the command line args are copied into 
	
	cImageTextures * mImage[IMAGE_TOTAL];	//cImageTextures are used as an example of aggregation
	int mIndex;								//index is used to keep track of controlled user loop 
	

};
#endif
