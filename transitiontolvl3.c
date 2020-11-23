#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "gamelvl3.h"
#include "transitiontolvl3.h"

#define FONT_SIZE 40.0f 
CP_Color fontColour1, fontColour2;


int displayheight, displaywidth;
void transitiontolvl3_init(void)
{

	displaywidth = 1280;
	displayheight = 720;



	CP_Settings_TextSize(FONT_SIZE);

}

void transitiontolvl3_update(void)
{

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	CP_Font_DrawText("Congratulations On Clearing Level 2 !", 250, 200);
	CP_Font_DrawText("Level 3 : Eliminate 25 Enemies", 300, 300);
	CP_Font_DrawText("Please press spacebar to proceed to level 3 !", 150, 400);

	fontColour2 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(fontColour2);
	CP_Font_DrawText("*Warning: Enemies in level 3 will be", 250, 500);
	CP_Font_DrawText("using special characters.", 350, 550);

	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game3_init, game3_update, game3_exit);
	}
}

void transitiontolvl3_exit(void)
{

}
