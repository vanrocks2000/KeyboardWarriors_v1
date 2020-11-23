#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "gamelvl2.h"
#include "transitiontolvl2.h"

#define FONT_SIZE 40.0f 
CP_Color fontColour1, fontColour2;


int displayheight, displaywidth;
void transitiontolvl2_init(void)
{
	
	displaywidth = 1280;
	displayheight = 720;
	
	
	
	CP_Settings_TextSize(FONT_SIZE);
	
}

void transitiontolvl2_update(void)
{
	CP_Font font1 = CP_Font_Load("./Assets/retro_computer.ttf");
	CP_Font_Set(font1);
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
	
	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	CP_Font_DrawText("Congratulations On Clearing Level 1 !", 250, 200);
	CP_Font_DrawText("Level 2 : Eliminate 25 Enemies", 300, 300);
	CP_Font_DrawText("Please press spacebar to proceed to level 2 !", 150, 400);
	
	fontColour2 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(fontColour2);
	CP_Font_DrawText("*Warning: Enemies in level 2 will be faster.", 200, 500);
	
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game2_init, game2_update, game2_exit);
	}
}

void transitiontolvl2_exit(void)
{

}
