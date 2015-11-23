/*Kelly Honsinger
Date Created:10/18/2015
Last Modification Date 11/9/2015
Lab Number: 5
File Name: main.cpp

Overview:
This Program is in the intermediate stage of becoming a game.  This game will display a sequence of images 
on the screen in random order.  A 'special' image will be amoungst these that the user must pay attention to. To
trigger the loop the user must direct a dot so that it collides with a start image.  After that a image loop will start that
will display a sequence of images in random order.  My "new feature" to my game is the ability to render the images in sync with eachother
so that there aren't any renderer gaps on the screen.  This is done by rendering seperate objects at the same time.  Contrary to popular belief,
no sprite sheet is being scrolled through here, seperate objects are.  Aggregrates and a composite can be found in the GameLoop class.

Input: 
The program takes its input via the command line arguments.

Output:
The program outputs the images that the command line arguments point to.
*/
#include "cGameLoop.h"

int main(int argc, char * argv[])
{

	cGameLoop StartGame(argv, argc);	//object that is passed command line args

	StartGame.BeginGame();				//object calls method to start game
	
	return 0;
}


