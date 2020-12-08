//---------------------------------------------------------
// file:	transitiontolvl2.c
// author:	Lee Yu Ting
// email:	yuting.lee@digipen.edu
//
// brief:	code for font size and font type done by Vanessa Luo
//          the rest of code done by Lee Yu Ting
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
#include "gamelvl2.h"
#include "transitiontolvl2.h"

#define FONT_SIZE 40.0f 
CP_Color fontColour1, fontColour2;
int displayheight, displaywidth;

void transitiontolvl2_init(void)
{
	//setting display width and height
	displaywidth = 1280;
	displayheight = 720;
	
	//setting font size
	CP_Settings_TextSize(FONT_SIZE);
	
}

void transitiontolvl2_update(void)
{
	//setting font type and colour
	CP_Font font1 = CP_Font_Load("./Assets/retro_computer.ttf");
	CP_Font_Set(font1);
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
	
	fontColour1 = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour1);
	//drawing text
	CP_Font_DrawText("Congratulations On Clearing Level 1 !", 250, 200);
	CP_Font_DrawText("Level 2 : Eliminate 25 Enemies", 300, 300);
	CP_Font_DrawText("Please press spacebar to proceed to level 2 !", 150, 400);
	
	//setting a different font color and drawing text
	fontColour2 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(fontColour2);
	CP_Font_DrawText("*Warning: Enemies in level 2 will be faster.", 200, 500);
	
	//changes gamestate when space is pressed
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(game2_init, game2_update, game2_exit);
	}
}

void transitiontolvl2_exit(void)
{

}
