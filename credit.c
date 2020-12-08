//---------------------------------------------------------
// file:	credit.c
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
#include "mainmenu.h"


#define FONT_SIZE 50.0f
#define FONT_SIZE2 40.0f
#define FONT_SIZE1 33.0f
#define FONT_SIZE3 25.0f

int displaywidth, displayheight;
float timee;

void credit_init(void)
{
	//sets the display width and height
	displayheight = 720;
	displaywidth = 1280;
	CP_System_SetWindowSize(displaywidth, displayheight);

	//sets the font type
	CP_Font font1 = CP_Font_Load("./Assets/retro_computer.ttf");
	CP_Font_Set(font1);
	
}

void credit_update(void)
{
	//loads and sets the background
	CP_Image bg = CP_Image_Load("./Assets/Bg2.png");
	CP_Image_Draw(bg, (float)displaywidth / 2, (float)displayheight / 2, (float)displaywidth, (float)displayheight, 125);
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 100));

	//sets the font colour and size and sets the alignment of text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(FONT_SIZE);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	
	//sets time
	timee += CP_System_GetDt();

	//displays first page of credits for the first 2 seconds
	if (timee < 2)
	{
		CP_Font_DrawTextBox("DIGIPEN INSTITUTE OF TECHNOLOGY\n\
        PRESENTS\n\
        ", 250, 100, 800);
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawTextBox("\n\
	    A Button Mashers PRODUCTION \n\
        \"Keyboard Warriors\"", 150, 300, 1000);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("WWW.DIGIPEN.EDU \n\
        COPYRIGHT 2020 BY DIGIPEN CORP, USA. ALL RIGHTS RESERVED.", 150, 520, 1000);
    
	}
	
	//displays second page of credits for the next 2 seconds
	if (timee > 2 && timee < 4)
	{
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("DEVELOPED BY\n", 250, 100, 800);
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawTextBox("Hau Hui Yang\n\
    Lee Yu Ting\n\
    Samuel Hsu\n\
    Vanessa Luo\n", 250, 150, 800);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Instructors\n", 250, 400, 800);
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawTextBox("Cheng Ding Xiang\n\
    Raymond Teo\n\
    ", 250, 450, 800);
	}

	//displays last page of credits after 4 seconds
	if (timee > 4)
	{
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("President\n", 250, 100, 800);
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawTextBox("CLAUDE COMAIR\n", 250, 150, 800);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Executives\n", 250, 250, 800);
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawTextBox("JASON CHU   JOHN BAUER\n\
	    SAMIR ABOU SAMRA   RAYMOND YAN\n\
	    PRASANNA GHALI   MICHELE COMAIR\n\
        XIN LI   ANGELA KUGLER\n\
        MELVIN GONSALVEZ   MEIGHAN MCKELVEY\n", 220, 300, 850);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox(">Press ESC to go back to main menu<", 200, 680, 1000);



	}
	
	
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}
	
	

}

void credit_exit(void)
{
	//set time to 0 and set text alignment back to default before leaving gamestate
	timee = 0;
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}