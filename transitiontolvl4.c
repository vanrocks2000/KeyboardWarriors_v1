#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "gamelvl3.h"
#include "transitiontolvl4.h"
#include "bosslvl.h"


#define FONT_SIZE 50.0f 
CP_Color fontColour1, fontColour2;


int displayheight, displaywidth;
void transitiontolvl4_init(void)
{

	displaywidth = 1280;
	displayheight = 720;



	CP_Settings_TextSize(FONT_SIZE);

}

void transitiontolvl4_update(void)
{

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	CP_Font_DrawText("Congratulations On Clearing Level 3 !", 300, 200);
	CP_Font_DrawText("Level 3 : Type 7 lines of sentences correctly to defeat the boss!", 350, 300);
	CP_Font_DrawText("Please press spacebar to proceed to level 3 !", 250, 400);

	fontColour2 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(fontColour2);
	CP_Font_DrawText("*Warning: Typing a sentence wrong will increase the speed of the boss.", 300, 500);

	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game4_init, game4_update, game4_exit);
	}
}

void transitiontolvl4_exit(void)
{

}
