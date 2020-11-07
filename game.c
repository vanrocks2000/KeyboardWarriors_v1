#include "cprocessing.h"
#include <stdio.h>

#define FONT_SIZE 50 
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10


// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
float characX = 100;
float characY = 100;

void game_init(void)
{
	

	CP_Settings_Background(CP_Color_Create(135, 245, 157, 255));
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// char colour[6] = {'H', 'E', 'L', 'L', 'O' };



	CP_Settings_TextSize(FONT_SIZE);
	//for (int i = 0; i < 5; i++)
	//{
	//	if (CP_Input_KeyTriggered(KEY_H) == colour[i] )
	//	{
	//		//CP_Font_DrawText(colour[i], characX, characY);
	//		CP_Font_DrawText("Correct", characX, characY);
	//	}
	//	else
	//	{
	//		CP_Font_DrawText("Wrong", characX, characY);
	//	}

	//	
	//}

	//if (CP_Input_KeyTriggered() == 72 )
	//{
	//	//CP_Font_DrawText(colour[i], characX, characY);
	//	CP_Font_DrawText("Correct", characX, characY);
	//}
	//else
	//{
	//	CP_Font_DrawText("Wrong", characX, characY);
	//}



	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{

}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation