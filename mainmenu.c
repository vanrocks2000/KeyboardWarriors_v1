#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "mainmenu.h"
#include "howtoplay.h"
#include "gamelvl3.h"
#define FONT_SIZE 100



void mainmenu_init(void)
{


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

		struct Button a1 , a2, a3;

		CP_Image_Draw(bg, (float)displayWidth / 2, (float)displayHeight / 2, (float)displayWidth, (float)displayHeight, 125);

		//setting size and position of buttons
		a1.width = 300;
		a1.height = 150;
		a1.x = (float)displayWidth / 2;
		a1.y = (float)displayHeight / 2.5f;

		a2.width = 300;
		a2.height = 150;
		a2.x = (float)displayWidth / 2;
		a2.y = (float)displayHeight / 1.65f;

		a3.width = 300;
		a3.height = 150;
		a3.x = (float)displayWidth / 2;
		a3.y = (float)displayHeight / 1.25f;

		//draw the logo, play & exit buttons on the screen

		//CP_Image logo = CP_Image_Load("./Assets/Logo.png");
		//CP_Image_Draw(logo, a1.x, a1.y, a3.width, a3.height, 255);

		CP_Image play = CP_Image_Load("./Assets/Play.png");
		CP_Image_Draw(play, a1.x , a1.y , a1.width, a1.height, 255);

		CP_Image howtoplay = CP_Image_Load("./Assets/HowToPlay.png");
		CP_Image_Draw(howtoplay, a2.x, a2.y, a1.width, a1.height, 255);

		CP_Image exit = CP_Image_Load("./Assets/Exit.png");
		CP_Image_Draw(exit, a3.x , a3.y , a1.width, a1.height, 255);

		/*
		CP_Color rectColour = CP_Color_Create(215, 196, 130, 255);
		CP_Settings_Fill(rectColour);
		CP_Graphics_DrawRect(a1.x, a1.y, a1.width, a1.height);
		CP_Graphics_DrawRect(a2.x, a2.y, a2.width, a2.height);

		CP_Settings_TextSize(FONT_SIZE);
		CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(fontColour);
		CP_Font_DrawText("Play", (float)displayWidth / 2.2f, (float)displayHeight / 3.5f);
		CP_Font_DrawText("Exit", (float)displayWidth / 2.2f, (float)displayHeight / 2.2f);
		*/

		float mouseX = CP_Input_GetMouseX(), mouseY = CP_Input_GetMouseY();
		//if mouse hover over buttons, change color of buttons
		if (mouseX > a1.x -150 && mouseX < (a1.x + a1.width))
		{
			if (mouseY > a1.y - 50 && mouseY < (a1.y - 50 + a1.height))
			{
				CP_Image play2 = CP_Image_Load("./Assets/Play2.png");
				CP_Image_Draw(play2, a1.x , a1.y , a1.width, a1.height, 255);

				/*
				CP_Color rectColour2 = CP_Color_Create(124, 126, 40, 255);
				CP_Settings_Fill(rectColour2);
				CP_Graphics_DrawRect(a1.x, a1.y, a1.width, a1.height);
				CP_Color fontColour2 = CP_Color_Create(255, 255, 255, 255);
				CP_Settings_Fill(fontColour2);

				CP_Settings_TextSize(FONT_SIZE);
				CP_Font_DrawText("Play", (float)displayWidth / 2.2f, (float)displayHeight / 3.5f);
				*/

				//if mouseclicked on first button, start the game
				if (CP_Input_MouseClicked())
				{
					CP_Engine_SetNextGameState(game_init, game_update, game_exit);
				}

			}
		}
		//Add code for How to play button
		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			CP_Engine_SetNextGameState(game3_init, game3_update, game3_exit);
		}
		if (mouseX > a1.x - 150 && mouseX < (a1.x + a1.width))
		{
			if (mouseY > a2.y - 50 && mouseY < (a2.y - 50 + a2.height))
			{
				CP_Image howtoplay2 = CP_Image_Load("./Assets/HowToPlay2.png");
				CP_Image_Draw(howtoplay2, a2.x, a2.y, a1.width, a1.height, 255);

				if (CP_Input_MouseClicked())
				{
					CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
				}
			}
		}

		if (mouseX > a2.x -150 && mouseX < (a2.x + a2.width))
		{
			if (mouseY > a2.y + 35 && mouseY < (a2.y + 35 + a2.height))
			{
				CP_Image exit2 = CP_Image_Load("./Assets/Exit2.png");
				CP_Image_Draw(exit2, a3.x , a3.y , a1.width, a1.height, 255);

				/*
				CP_Color rectColour2 = CP_Color_Create(124, 126, 40, 255);
				CP_Settings_Fill(rectColour2);
				CP_Graphics_DrawRect(a2.x, a2.y, a2.width, a2.height);
				CP_Color fontColour2 = CP_Color_Create(255, 255, 255, 255);
				CP_Settings_Fill(fontColour2);

				CP_Settings_TextSize(FONT_SIZE);
				CP_Font_DrawText("Exit", (float)displayWidth / 2.2f, (float)displayHeight / 2.2f);
				*/

				//if mouseclicked on the seocnd button, terminates game
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