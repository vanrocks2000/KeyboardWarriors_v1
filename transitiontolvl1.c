//---------------------------------------------------------
// file:	transitiontolvl1.c
// author:	Vanessa Luo
// email:	vanessa.l@digipen.edu
//
// brief:	done by Vanessa Luo
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
#include "game.h"
#include "transitiontolvl1.h"

#define FONT_SIZE 50.0f 
CP_Color fontColour1, fontColour2;


int displayheight, displaywidth;
void transitiontolvl1_init(void)
{

	displaywidth = 1280;
	displayheight = 720;
	CP_System_SetWindowSize(displaywidth, displayheight);



	CP_Settings_TextSize(FONT_SIZE);


}

void transitiontolvl1_update(void)
{
	CP_Font font1 = CP_Font_Load("./Assets/retro_computer.ttf");
	CP_Font_Set(font1);
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));	
	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	CP_Font_DrawText("Level 1: Elminate 15 enemies", 250, 300);
	CP_Font_DrawText("Please press spacebar to proceed", 150, 400);


	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}
}

void transitiontolvl1_exit(void)
{

}
