//---------------------------------------------------------
// file:	mainmenu.c
// author:	Vanessa Luo
// email:	vanessa.l@digipen.edu
//
// brief:	Background/Buttons and Art done by HuiYang
//			Initial Base code of buttons done by Vanessa
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "mainmenu.h"
#include "howtoplay.h"
#include "bosslvl.h"
#include "transitiontolvl1.h"
#include "credit.h"

#define FONT_SIZE 100



void mainmenu_init(void)
{
	CP_System_SetWindowTitle("KEYBOARD WARRIORS");

	int displayWidth = 1280;
	int displayHeight = 720;

	CP_System_SetWindowSize(displayWidth, displayHeight);

	//Loads digipen logo
	CP_Image DPlogo = CP_Image_Load("./Assets/DigiPen_BLACK.png");
	CP_Image bg = CP_Image_Load("./Assets/bg.png");

	float time = CP_System_GetSeconds();

	if (time < 3)
	{
		CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
		CP_Image_Draw(DPlogo, (float)displayWidth / 2, (float)displayHeight / 2, (float)CP_Image_GetWidth(DPlogo), (float)CP_Image_GetHeight(DPlogo), 255);
	}
	else
	{

		struct Button a1 , a2, a3, a4;

		CP_Image_Draw(bg, (float)displayWidth / 2, (float)displayHeight / 2, (float)displayWidth, (float)displayHeight, 125);

		//setting size and position of buttons
		a1.width = 300;
		a1.height = 150;
		a1.x = (float)displayWidth / 2.75f;
		a1.y = (float)displayHeight / 2.3f;

		a2.width = 300;
		a2.height = 150;
		a2.x = (float)displayWidth / 1.5f;
		a2.y = (float)displayHeight / 2.3f;

		a3.width = 350;
		a3.height = 150;
		a3.x = (float)displayWidth / 2.75f;
		a3.y = (float)displayHeight / 1.35f;

		a4.width = 300;
		a4.height = 150;
		a4.x = (float)displayWidth / 1.5f;
		a4.y = (float)displayHeight / 1.35f;

		//draw the play, howtoplay, credits & exit buttons on the screen

		CP_Image play = CP_Image_Load("./Assets/Play.png");
		CP_Image_Draw(play, a1.x , a1.y , a1.width, a1.height, 255);

		CP_Image howtoplay = CP_Image_Load("./Assets/HowToPlay.png");
		CP_Image_Draw(howtoplay, a2.x, a2.y, a1.width, a1.height, 255);

		CP_Image credits = CP_Image_Load("./Assets/Credits.png");
		CP_Image_Draw(credits, a3.x, a3.y, a3.width, a3.height, 255);

		CP_Image exit = CP_Image_Load("./Assets/Exit.png");
		CP_Image_Draw(exit, a4.x , a4.y , a4.width, a4.height, 255);

		// get x & y position of mouse
		float mouseX = CP_Input_GetMouseX(), mouseY = CP_Input_GetMouseY();

		//if mouse hover over buttons, change color of buttons

		//Play button
		if (mouseX > a1.x -150 && mouseX < (a1.x + a1.width / 2))
		{
			if (mouseY > a1.y - 50 && mouseY < (a1.y - 50 + a1.height))
			{
				CP_Image play2 = CP_Image_Load("./Assets/Play2.png");
				CP_Image_Draw(play2, a1.x , a1.y , a1.width, a1.height, 255);

				//if mouseclicked on first button, start the game
				if (CP_Input_MouseClicked())
				{
					CP_Engine_SetNextGameState(transitiontolvl1_init, transitiontolvl1_update, transitiontolvl1_exit);
				}

			}
		}

		//How to play button

		if (mouseX > a2.x - 150 && mouseX < (a2.x + a1.width / 2))
		{
			if (mouseY > a2.y - 50 && mouseY < (a2.y - 50 + a2.height))
			{
				CP_Image howtoplay2 = CP_Image_Load("./Assets/HowToPlay2.png");
				CP_Image_Draw(howtoplay2, a2.x, a2.y, a2.width, a2.height, 255);

				//if mouseclicked on the second button, load how to play page
				if (CP_Input_MouseClicked())
				{
					CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
				}
			}
		}

		//Credits button
		
		// if player presses space 

		if (mouseX > a3.x - 150 && mouseX < (a3.x + a3.width / 2))
		{
			if (mouseY > a3.y - 50 && mouseY < (a3.y - 50 +  a3.height))
			{
				CP_Image credits2 = CP_Image_Load("./Assets/Credits2.png");
				CP_Image_Draw(credits2, a3.x, a3.y, a3.width, a3.height, 255);

				//if mouseclicked on the second button, load credits page
				if (CP_Input_MouseClicked())
				{
					//load credits page
					CP_Engine_SetNextGameState(credit_init, credit_update, credit_exit);
				}
			}
		}

		//Exit button
		if (mouseX > a4.x -150 && mouseX < (a4.x + a4.width / 2))
		{
			if (mouseY > a4.y - 50 && mouseY < (a4.y - 50 + a4.height))
			{
				CP_Image exit2 = CP_Image_Load("./Assets/Exit2.png");
				CP_Image_Draw(exit2, a4.x , a4.y , a4.width, a4.height, 255);

				//if mouseclicked on the second button, terminates game
				if (CP_Input_MouseClicked())
				{
					CP_Engine_Terminate();
				}
			}
		}
	}
}

void mainmenu_update(void)
{

	mainmenu_init();
}

void mainmenu_exit(void)
{

}