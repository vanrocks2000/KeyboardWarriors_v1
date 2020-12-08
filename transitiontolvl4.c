//---------------------------------------------------------
// file:	transitiontolvl4.c
// author:	Lee Yu Ting
// email:	yuting.lee@digipen.edu
//
// brief:	code done by Lee Yu Ting
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
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

#define FONT_SIZE 40.0f 
CP_Color fontColour1, fontColour2;
int displayheight, displaywidth;

void transitiontolvl4_init(void)
{
	//setting display width and height
	displaywidth = 1280;
	displayheight = 720;

	//setting font size
	CP_Settings_TextSize(FONT_SIZE);

}

void transitiontolvl4_update(void)
{
	
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
	
	//setting font colour and drawing text
	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	CP_Font_DrawText("Congratulations On Clearing Level 3 !", 225, 200);
	CP_Font_DrawText("Level 4 : Type 7 sentences correctly to defeat boss!", 50, 300);
	CP_Font_DrawText("Please press spacebar to proceed to level 4 !", 140, 400);

	fontColour2 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(fontColour2);
	CP_Font_DrawText("*Warning: Typing a sentence wrong will ", 225, 500);
	CP_Font_DrawText("increase the speed of the boss.", 310, 550);

	//changes gamestate when space is pressed
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game4_init, game4_update, game4_exit);
	}
}

void transitiontolvl4_exit(void)
{

}
